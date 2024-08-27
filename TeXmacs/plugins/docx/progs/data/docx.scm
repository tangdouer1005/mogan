;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; MODULE      : docx.scm
;; DESCRIPTION : DOCX data format
;; COPYRIGHT   : (C) 2024  ATQlove
;;
;; This software falls under the GNU general public license version 3 or later.
;; It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
;; in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(import (liii uuid))
(texmacs-module (data docx)
  (:use (binary pandoc)
        (texmacs texmacs tm-files)
        (network url)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DOCX format defination
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-format docx
  (:name "docx")
  (:suffix "docx"))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Function to export TeXmacs document to DOCX using Pandoc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tm-define (texmacs-tree->docx-string t opt)
  (:synopsis "Export TeXmacs document to DOCX format using Pandoc")
  (let* (
         (temp-name (string-append "/" (uuid4)))  
         (temp-dir (string-append (url->string (url-temp-dir)) temp-name))
         (html-temp-url (system->url (string-append temp-dir ".html")))
         (docx-temp-url (system->url (string-append temp-dir ".docx"))))
    ;; First, export the document to HTML
    (string-save (serialize-html (texmacs->html t opt)) html-temp-url)
    ;; Then, use Pandoc to convert the HTML to DOCX
    (if (has-binary-pandoc?)
        (let ((cmd (string-append (url->string (find-binary-pandoc))
                                  " -f html -t docx "
                                  (url->string html-temp-url)
                                  " -o "
                                  (url->string docx-temp-url))))
          (system cmd)
          (with result (string-load docx-temp-url)
            (system-remove html-temp-url)
            (system-remove docx-temp-url)
            result)
          ;; Delete the intermediate HTML file
          ) ;; Expected:$TEXMACS_PATH/tests/tm.html")
        (error "Pandoc binary not found"))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Converter for exporting TeXmacs tree to DOCX string
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(converter texmacs-tree docx-document
  (:require (has-binary-pandoc?))
  (:function-with-options texmacs-tree->docx-string)
  (:option "texmacs->html:css" "on")
  (:option "texmacs->html:mathjax" "off")
  (:option "texmacs->html:mathml" "off")
  (:option "texmacs->html:images" "on")
  (:option "texmacs->html:css-stylesheet" "---"))
