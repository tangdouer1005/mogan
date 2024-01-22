<TeXmacs|2.1.2>

<style|<tuple|tmdoc|british|devel>>

<\body>
  <tmdoc-title|Failed to visit local link in remote doc>

  <section|Bug Metadata>

  <\itemize>
    <item>Reporter: Darcy on <hlink|Gitee|https://gitee.com/XmacsLabs/mogan/issues/I5GL0I>

    <item>Owner: <value|da>

    <item>Tester: <value|da>
  </itemize>

  <section|How to reproduce it>

  Click the rooted local file link in the remote doc.

  <section|Solution>

  <subsection|The root cause>

  The <scm|url_handlers> does not work properly for rooted local files.

  <subsection|How to fix it>

  Correct the <scm|url-handlers>:

  <slink|file:///$TEXMACS_PATH/progs/link/link-navigate.scm>

  <subsection|How to test it>

  Follow how to reproduce it.

  <tmdoc-copyright|2023|Who>

  <tmdoc-license|Permission is granted to copy, distribute and/or modify this
  document under the terms of the GNU Free Documentation License, Version 1.1
  or any later version published by the Free Software Foundation; with no
  Invariant Sections, with no Front-Cover Texts, and with no Back-Cover
  Texts. A copy of the license is included in the section entitled "GNU Free
  Documentation License".>
</body>

<\initial>
  <\collection>
    <associate|page-medium|papyrus>
  </collection>
</initial>