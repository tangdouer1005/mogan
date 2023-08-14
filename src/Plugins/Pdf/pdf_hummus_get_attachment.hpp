/******************************************************************************
* MODULE     : pdf_hummus_renderer.hpp
* DESCRIPTION: Interface for embedding text files into pdf files
* COPYRIGHT  : (C) 2023 Tangdouer
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/
#ifndef PDF_HUMMUS_GET_ATTACHMENT_H
#define PDF_HUMMUS_GET_ATTACHMENT_H
#include "hashmap.hpp"
#include "iterator.hpp"
#include "list.hpp"
#include "string.hpp"
#include "tm_ostream.hpp"
#include "url.hpp"

bool get_tm_attachments_in_pdf(url pdf_path, array<string> &names, array<string> &s);

bool get_tm_attachment_in_pdf(url pdf_path, string &s);

#endif // ifdef PDF_HUMMUS_MAKE_ATTACHMENT_H