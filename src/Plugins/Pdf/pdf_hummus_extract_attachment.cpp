/******************************************************************************
 * MODULE     : pdf_hummus_extract_attachment.cpp
 * DESCRIPTION: Interface for extract attachment file in pdf
 * COPYRIGHT  : (C) 2023 Tangdouer
 *******************************************************************************
 * This software falls under the GNU general public license version 3 or later.
 * It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
 * in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
 ******************************************************************************/
#include "PDFWriter/PDFWriter.h"
#include "PDFWriter/SafeBufferMacrosDefs.h"
#include "PDFWriter/Trace.h"

#include "PDFWriter/InputFileStream.h"
#include "PDFWriter/OutputBufferedStream.h"
#include "PDFWriter/OutputFileStream.h"
#include "PDFWriter/OutputStreamTraits.h"
#include "PDFWriter/PDFArray.h"
#include "PDFWriter/PDFLiteralString.h"
#include "PDFWriter/PDFObjectCast.h"
#include "PDFWriter/PDFParser.h"
#include "PDFWriter/PDFStreamInput.h"
using namespace PDFHummus;
using namespace IOBasicTypes;
#include "pdf_hummus_extract_attachment.hpp"
#include "tm_debug.hpp"
#include "file.hpp"
#include "tm_url.hpp"
#include "analyze.hpp"
#include "tree_helper.hpp"
bool
extract_attachments_from_pdf (url pdf_path, list<url>& names) {
  EStatusCode status= PDFHummus::eSuccess;
  InputFile   pdfFile;
  PDFParser   parser;
  do {
    status= pdfFile.OpenFile (as_charp (as_string (pdf_path)));
    if (status != PDFHummus::eSuccess) {
      if (DEBUG_CONVERT)
        debug_convert << "fail to open " << as_string (pdf_path) << LF;
      break;
    }
    parser.StartPDFParsing (pdfFile.GetInputStream ());
    PDFObjectCastPtr<PDFDictionary> catalog (
        parser.QueryDictionaryObject (parser.GetTrailer (), "Root"));
    // return 0;
    if (!catalog) {
      if (DEBUG_CONVERT) debug_convert << "Can't find catalog. fail\n";
      status= PDFHummus::eFailure;
      break;
    }

    PDFObjectCastPtr<PDFDictionary> d_1 (catalog->QueryDirectObject ("Names"));
    if (!d_1) {
      if (DEBUG_CONVERT) debug_convert << "Can't find d1. fail\n";
      status= PDFHummus::eFailure;
      break;
    }
    PDFObjectCastPtr<PDFDictionary> d_2 (
        d_1->QueryDirectObject ("EmbeddedFiles"));
    if (!d_2) {
      if (DEBUG_CONVERT) debug_convert << "Can't find d2. fail\n";
      status= PDFHummus::eFailure;
      break;
    }

    PDFObjectCastPtr<PDFArray> arr (d_2->QueryDirectObject ("Names"));
    if (!arr) {
      if (DEBUG_CONVERT) debug_convert << "Can't find arr. fail\n";
      status= PDFHummus::eFailure;
      break;
    }
    unsigned long n= arr->GetLength ();
    // Every two elements in the array represent an attachment
    if (n == 0) {
      if (DEBUG_CONVERT) debug_convert << "arr->GetLength () is 0\n";
      status= PDFHummus::eFailure;
      break;
    }
    if (n & 1) {
      if (DEBUG_CONVERT) debug_convert << "arr->GetLength () is wrong\n";
      status= PDFHummus::eFailure;
      break;
    }
    for (unsigned long i= 0; i < n; i+= 2) {
      PDFObjectCastPtr<PDFLiteralString> name (arr->QueryObject (i));
      if (!name) {
        if (DEBUG_CONVERT)
          debug_convert << "Can't find arr->QueryObject (" << i << ")\n";
        status= PDFHummus::eFailure;
        break;
      }
      PDFObjectCastPtr<PDFDictionary> arr_d1 (arr->QueryObject (i + 1));
      if (!arr_d1) {
        if (DEBUG_CONVERT)
          debug_convert << "Can't find arr->QueryObject (" << i + 1 << ")\n";
        status= PDFHummus::eFailure;
        break;
      }
      PDFObjectCastPtr<PDFDictionary> arr_d2 (arr_d1->QueryDirectObject ("EF"));
      if (!arr_d2) {
        if (DEBUG_CONVERT) debug_convert << "Can't find arr_d2\n";
        status= PDFHummus::eFailure;
        break;
      }
      PDFObjectCastPtr<PDFStreamInput> stream (
          parser.QueryDictionaryObject (arr_d2.GetPtr (), "F"));
      if (!stream) {
        if (DEBUG_CONVERT) debug_convert << "Can't find stream\n";
        status= PDFHummus::eFailure;
        break;
      }
      PDFDictionary* dir= stream->QueryStreamDictionary ();

      IByteReader* streamReader=
          parser.CreateInputStreamReader (stream.GetPtr ());
      if (!streamReader) {
        if (DEBUG_CONVERT) debug_convert << "Can't find streamReader\n";
        status= PDFHummus::eFailure;
        break;
      }

      url attachment_path=
          relative (pdf_path, url (string (name->GetValue ().c_str ())));
      OutputFile attachment_file;
      status= attachment_file.OpenFile (
          std::string (as_charp (as_string (attachment_path))));
      if (status != PDFHummus::eSuccess) {
        if (DEBUG_CONVERT)
          debug_convert << "fail to open " << as_string (attachment_path) << LF;
        break;
      }
      pdfFile.GetInputStream ()->SetPosition (stream->GetStreamContentStart ());
      OutputStreamTraits copy_help (
          (IByteWriter*) attachment_file.GetOutputStream ());
      status= copy_help.CopyToOutputStream (streamReader);
      if (status != PDFHummus::eSuccess) {
        if (DEBUG_CONVERT) debug_convert << "Can't CopyToOutputStream\n";
        break;
      }
      status= attachment_file.CloseFile ();
      if (status != PDFHummus::eSuccess) {
        if (DEBUG_CONVERT)
          debug_convert << "fail to close " << as_string (attachment_path)
                        << LF;
        break;
      }

      names= names * attachment_path;
      delete streamReader;
    }
  } while (0);
  if (status == PDFHummus::eFailure) return false;
  else return true;
}

bool
scm_extract_attachments (url pdf_path) {
  cout << "scm_extract_attachments " << pdf_path << LF;
  list<url> attachments_paths;
  bool ret = extract_attachments_from_pdf (pdf_path, attachments_paths);
  cout << "attachments_paths -> " << attachments_paths << LF;
  return ret;
}
static hashset<string> internal_styles;

static void
declare_style (url u) {
  if (is_or (u)) {
    declare_style (u[1]);
    declare_style (u[2]);
  }
  else if (is_concat (u)) {
    string dir= upcase_first (as_string (u[1]));
    if (dir == "CVS" || dir == ".svn");
    else declare_style (u[2]);
  }
  else if (is_atomic (u)) {
    string s= as_string (u);
    if (ends (s, ".ts") && !starts (s, "source")) {
      internal_styles->insert (s(0,N(s)-3));
      if (starts (s, "old-"))
        internal_styles->insert (s(4,N(s)-3));
      if (starts (s, "old2-"))
        internal_styles->insert (s(5,N(s)-3));
    }
  }
}

static bool
is_internal_style (string style) {
  return true;

  if (N (internal_styles) == 0) {
    url sty_u= descendance ("$TEXMACS_STYLE_ROOT");
    declare_style (sty_u);
  }
  return internal_styles->contains (style);
}

array<url> get_linked_file_paths(tree t){
  list<tree> st (t);
  array<url>  tm_and_linked_file;
  while (N (st) != 0) {
    auto la= last_item (st);
    st     = suppress_last (st);
    for (int i= 0; i < arity (la); i++) {
      if (is_compound (la[i])) {
        string label= la[i] -> label;
        if (label == "image" || label == "include") {
          if (is_atomic (la[i][0])) {
            url pre_url= url (la[i][0]->label);
            if (!exists (pre_url)) {
                debug_convert << pre_url << "do not exist" << LF;
            }
            tm_and_linked_file= append (pre_url, tm_and_linked_file);
          }
        }
        else if (label == "style") {
          if (is_tuple (la[i][0])) {
            for (int j= 0; j < N (la[i][0]); j++) {
              string style_name= la[i][0][j] -> label;
              if (!is_internal_style (style_name)) {
                url style_url= url (style_name);
                style_url    = glue (style_url, ".ts");
                if (!exists (style_url)) {
                    debug_convert << style_url << "do not exist" << LF;
                }
                tm_and_linked_file= append(style_url, tm_and_linked_file);
              }
            }
          }
          else {
            if (!is_atomic (la[i][0])) {
              debug_convert << la[i][0] -> label << "is not atomic tree" << LF;
            }
            string style_name= la[i][0] -> label;
            if (!is_internal_style (style_name)) {
              url style_url= url (style_name);
              style_url    = glue (style_url, ".ts");
              if (!exists (style_url)) {
                    debug_convert << style_url << "do not exist" << LF;
              }
              tm_and_linked_file= append(style_url, tm_and_linked_file);
            }
          }
        }
        else st= st * la[i];
      }
    }
  }
  
  return tm_and_linked_file;
}

tree replace_with_relative_path(tree t){
   // dfs search all style and link
  list<tree> st (t);
  list<url>  tm_and_linked_file;
  //url cur_u = get_current_buffer ();
  while (N (st) != 0) {
    auto la= last_item (st);
    st     = suppress_last (st);
    for (int i= 0; i < arity (la); i++) {
      if (is_compound (la[i])) {
        string label= la[i] -> label;
        if (label == "image" || label == "include") {
          if (is_atomic (la[i][0])) {
            url pre_url= url (la[i][0]->label);
            if (!exists (pre_url)) {
              // pre_url= head (cur_u) * pre_url;
              // if (!exists (pre_url)) {
                debug_convert << pre_url << "do not exist" << LF;
              //}
            }
            string name       = as_string (tail (pre_url));
            la[i][0]->label   = string (name);
          }
        }
        else if (label == "style") {
          if (is_tuple (la[i][0])) {
            for (int j= 0; j < N (la[i][0]); j++) {
              string style_name= la[i][0][j] -> label;
              if (!is_internal_style (style_name)) {
                url style_url= url (style_name);
                style_url    = glue (style_url, ".ts");
                if (!exists (style_url)) {
                  // style_url= head (cur_u) * style_url;
                  // if (!exists (style_url)) {
                    debug_convert << style_url << "do not exist" << LF;
                  //}
                }
                string name       = basename (style_url);
                la[i][0][j]->label= name;
              }
            }
          }
          else {
            if (!is_atomic (la[i][0])) {
              debug_convert << la[i][0] -> label << "is not atomic tree" << LF;
            }
            string style_name= la[i][0] -> label;
            if (!is_internal_style (style_name)) {
              url style_url= url (style_name);
              style_url    = glue (style_url, ".ts");
              if (!exists (style_url)) {
                // style_url= head (cur_u) * style_url;
                // if (!exists (style_url)) {
                    debug_convert << style_url << "do not exist" << LF;
                //}
              }
              string name= basename (style_url);
              la[i][0]->label= name;
            }
          }
        }
        else st= st * la[i];
      }
    }
  }
  return t;
}


url get_main_tm(url pdf_path){
  list<url> attachments_paths;
  bool ret = extract_attachments_from_pdf (pdf_path, attachments_paths);
  return attachments_paths[0];
}