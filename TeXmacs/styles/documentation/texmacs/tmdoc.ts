<TeXmacs|2.1>

<style|<tuple|source|english>>

<\body>
  <\active*>
    <\src-title>
      <src-style-file|tmdoc|1.0>

      <\src-purpose>
        Style for the <TeXmacs> documentation.
      </src-purpose>

      <\src-copyright|2002--2004>
        Joris van der Hoeven
      </src-copyright>

      <\src-license>
        This software falls under the <hlink|GNU general public license,
        version 3 or later|$TEXMACS_PATH/LICENSE>. It comes WITHOUT ANY
        WARRANTY WHATSOEVER. You should have received a copy of the license
        which the software. If not, see <hlink|http://www.gnu.org/licenses/gpl-3.0.html|http://www.gnu.org/licenses/gpl-3.0.html>.
      </src-license>
    </src-title>
  </active*>

  <use-package|std|env|title-generic|header-article|section-article|doc>

  <\active*>
    <\src-comment>
      Global style parameters.
    </src-comment>
  </active*>

  <assign|par-hyphen|professional>

  <assign|par-par-sep|0.5fn>

  <assign|par-first|0fn>

  <assign|padded-par-par-sep|0.5fn>

  <assign|indent-par-first|1.5fn>

  <assign|save-aux|false>

  <assign|sectional-sep|<macro|.<space|2spc>>>

  <assign|sectional-post-sep|<macro|<space|2spc>>>

  <assign|html-css|https://www.texmacs.org/css/tmdoc.css>

  <assign|html-head-javascript-src|https://www.texmacs.org/javascript/texmacs_functions.js>

  <\active*>
    <\src-comment>
      Sections, subsections and subsubsections.
    </src-comment>
  </active*>

  <assign|sectional-sep|<macro|.<space|2spc>>>

  <assign|section-font|<macro|name|<large|<arg|name>>>>

  <assign|subsection-font|<macro|name|<arg|name>>>

  <assign|subsubsection-font|<macro|name|<arg|name>>>

  \;

  <assign|section-title|<macro|name|<style-with|src-compact|none|<sectional-normal-bold|<vspace*|1.25fn><section-font|<arg|name>><vspace|0.5fn>>>>>

  <assign|subsection-title|<macro|name|<style-with|src-compact|none|<sectional-normal-bold|<vspace*|1fn><subsection-font|<arg|name>><vspace|0.5fn>>>>>

  <assign|subsubsection-title|<macro|name|<style-with|src-compact|none|<sectional-normal-bold|<vspace*|0.5fn><subsubsection-font|<arg|name>><vspace|0.25fn>>>>>

  <\active*>
    <\src-comment>
      Paragraphs and subparagraphs.
    </src-comment>
  </active*>

  \;

  <assign|paragraph-font|<macro|name|<with|font-shape|italic|<arg|name>>>>

  <assign|subparagraph-font|<macro|name|<with|font-shape|italic|<arg|name>>>>

  <assign|paragraph-title|<macro|name|<style-with|src-compact|none|<sectional-short|<vspace*|0.5fn><paragraph-font|<arg|name>>>>>>

  <assign|subparagraph-title|<macro|name|<style-with|src-compact|none|<sectional-short|<vspace*|0.5fn><subparagraph-font|<arg|name>>>>>>

  <\active*>
    <\src-comment>
      Other customizations.
    </src-comment>
  </active*>

  <assign|enunciation-name|<macro|name|<with|font-shape|small-caps|<arg|name>>>>

  <active*|<\src-comment>
    Typewriter font.
  </src-comment>>

  <assign|tt-font-base|<macro|x|<with|font|roman|font-family|tt|magnification|<times|<value|magnification>|1.06>|<arg|x>>>>

  <assign|tt-font|<macro|x|<tt-font-base|<arg|x>>>>

  <assign|tt-prog-font|<macro|x|<tt-font-base|<arg|x>>>>

  <assign|tt-session-font|<macro|x|<with|font|typewriter=CMU,roman|<arg|x>>>>

  \;

  <assign|verbatim|<macro|body|<with|language|verbatim|<tt-font|<arg|body>>>>>

  <assign|shell|<macro|body|<with|mode|prog|prog-language|shell|<tt-prog-font|<arg|body>>>>>

  <assign|scm|<macro|body|<with|mode|prog|prog-language|scheme|<tt-prog-font|<arg|body>>>>>

  <assign|cpp|<macro|body|<with|mode|prog|prog-language|cpp|<tt-prog-font|<arg|body>>>>>

  <assign|python|<macro|body|<with|mode|prog|prog-language|python|<tt-prog-font|<arg|body>>>>>

  <active*|<\src-comment>
    Hacks for the typewriter font in plug-in sessions.
  </src-comment>>

  <assign|scheme-input|<\macro|prompt|body>
    <\with|generic-prompt-color|<value|scheme-prompt-color>|generic-input-color|<value|scheme-input-color>>
      <tt-font|<generic-input|<arg|prompt>|<arg|body>>>
    </with>
  </macro>>

  <assign|input|<macro|prompt|body|<with|mode|prog|font-family|rm|<tt-session-font|<style-with|src-compact|none|<compound|<style-with|src-compact|none|<if|<provides|<merge|<value|prog-language>|-input>>|<merge|<value|prog-language>|-input>|generic-input>>|<arg|prompt>|<arg|body>>>>>>>

  <assign|output|<macro|body|<with|mode|prog|font-family|rm|<tt-session-font|<style-with|src-compact|none|<compound|<style-with|src-compact|none|<if|<provides|<merge|<value|prog-language>|-output>>|<merge|<value|prog-language>|-output>|generic-output>>|<arg|body>>>>>>>

  <assign|script-input|<macro|language|session|in|out|<tt-session-font|<style-with|src-compact|none|<compound|<style-with|src-compact|none|<if|<provides|<merge|<arg|language>|-script-input>>|<merge|<arg|language>|-script-input>|generic-script-input>>|<arg|language>|<arg|session>|<arg|in>|<arg|out>>>>>>
</body>

<\initial>
  <\collection>
    <associate|preamble|true>
  </collection>
</initial>