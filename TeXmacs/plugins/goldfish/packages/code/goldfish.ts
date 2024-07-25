<TeXmacs|2.1.2>

<style|source>

<\body>
  <active*|<\src-title>
    <src-package|goldfish|1.0>

    <\src-purpose>
      Markup for Scheme defined in R7RS.
    </src-purpose>

    <src-copyright|2024|Darcy Shen>

    <\src-license>
      This software falls under the <hlink|GNU general public license,
      version 3 or later|$TEXMACS_PATH/LICENSE>. It comes WITHOUT ANY
      WARRANTY WHATSOEVER. You should have received a copy of the license
      which the software. If not, see <hlink|http://www.gnu.org/licenses/gpl-3.0.html|http://www.gnu.org/licenses/gpl-3.0.html>.
    </src-license>
  </src-title>>

  <use-module|(data r7rs)>

  <use-module|(code goldfish-edit)>

  <assign|goldfish-prompt-color|dark green>

  <assign|goldfish-input|<\macro|prompt|body>
    <\with|generic-prompt-color|<value|goldfish-prompt-color>|generic-input-color|<value|scheme-input-color>>
      <generic-input|<arg|prompt>|<with|prog-language|r7rs|<arg|body>>>
    </with>
  </macro>>

  \;

  <assign|goldfish-result|<\macro|body>
    <with|ornament-border|0ln|ornament-hpadding|0spc|padding-above|0fn|padding-below|0fn|ornament-color|pastel
    green|<\ornamented>
      <arg|body>
    </ornamented>>
  </macro>>
</body>

<initial|<\collection>
</collection>>
