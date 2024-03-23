# Comment
Any character after tilde won’t be parsed until newline or the end of document.

```gr
Now you see me. ~ Now you dont.
```

```html
<p>Now you see me.</p>
```

# Annotation
## Document Metadata
First annotation at the begining of document belongs to `Document` node.

```regex
~~ [a-zA-Z-0-9-]+:.*
```

```gr
~~ title: Book Title
~~ author: Author Name
~~ created-at: 2021-01-10
~~ published-at: 2024-01-03
~~ category: Science-Fiction

```

## Entity Annotation
```gr
~~ text-alignment: center
A paragraph annotation
```

```html
<p class="text-alignment--center">A paragraph annotation</p>
```

# Paragraph
```gr
Any text without special modifier will be rendered as paragraph.
Single new line won't make new paragraph.

Only double or more will create new paragraph.
```

```html
<p>Any text without special modifier will be rendered as paragraph.
Single new line won't make new paragraph.</p>

<p>Only double or more will create new paragraph.</p>
```

# Style
```gr
*Anything inside two asterisks will be rendered as bold font style.*
```

```html
<p><b>Anything inside two asterisks will be rendered as bold font style.</b></p>
```

```gr
_Anything inside two underscores will be rendered as italic font style._
```

```html
<p><i>Anything inside two underscores will be rendered as italic font style.</i></p>
```

```gr
Hello _*darkness* my old_ friend
```

```html
<p>Hello <i><b>darkness</b> my old</i> friend</p>
```

# Highlight
```gr
=Anything inside two equal will be rendered as highlighted=
```

```html
<p><mark>Anything inside two equal will be rendered as highlighted</mark></p>
```

# Breaking
## Thematic‐Break
```gr
***
```

```html
<hr>
```

## Line‐Break
```gr
This will create<<line-break.
```

```html
<p>This will create<br>line-break.</p>
```

## Page‐Break
```gr
<<<
```

```html
<div class="page-break"></div>
```

# Escape
Anything after backslash is will be rendered as is

```gr
\*escaped
```

```html
<p>*escaped</p>
```

# Quote
Quote is done by indenting with tabs.

```gr 
	"You have power over your mind---not outside events. Realize this, and you will find strength." 
	--Markus Aurelius
```

```html
<blockquote>
	<p>&#8223;You have power over your mind&#8212;not outside events. Realize this, and you will find strength.&#8221;
	&#8211;Markus Aurelius</p>
</blockquote>
```

### Nested Quote
```gr
		"You have power over your mind---not outside events. Realize this, and you will find strength." 
		--Markus Aurelius
	Say what now?
```

```html
<blockquote>
	<blockquote>
		<p>&#8223;You have power over your mind&#8212;not outside events. Realize this, and you will find strength.&#8221;
		&#8211;Markus Aurelius</p>
	</blockquote>
	<p>Say what now?</p>
</blockquote>
```

# Heading
```gr
>>> Section

>> Subection

> Subsubsection
```

```html
<h1 id="Section">Section</h1>

<h2 id="Subection">Subsection</h2>

<h3 id="Subsubsection">Subsubsection</h3>
```

## Heading Subtitle
If the subsection modifier is placed in the next line of any headings. It will be parsed as subtitle.

```gr
>>> Section
> Section Subtitle

>> Subsection
> Subsection Subtitle

> Subsubsection
> Subsubsection Subtitle
```

```html
<h1 id="Section">Section <small>Section Subtitle</small></h1>

<h2 id="Subsection">Subsection <small>Subsection Subtitle</small></h2>

<h3 id="Subsubsection">Subsubsection <small>Subsubsection Subtitle</small><h3>
```

## Heading Link
```gr
>>> Laminal Flow

See [>Laminal Flow]

If on another file [Chapter 1.gr>Laminal Flow]
```

```html
<h1 id="Laminar-Flow">Laminar Flow</h1>

<p>See <a href="#Laminar-Flow">Laminal Flow</a></p>

<p>If on another file <a href="Chapter 1.gr#Laminal-Flow">Chapter 1.gr Laminal Flow</a></p>
```

# List
## Bullet List
```gr
- Fast
- Furious
- Fit
```

```html
<ul>
	<li>Fast</li>
	<li>Furious</li>
	<li>Fit</li>
</ul>
```

## Numbered List
```gr
1. One
2. Two 
3. Three
```

```html
<ol>
	<li>One</li>
	<li>Two</li>
	<li>Three</li>
</ol>
```

## Nested Variation
```gr
- One 
- Two 
	- Two sub 1
	- Two sub 2
		- Two sub 2 section A 
		- Two sub 2 section B
	- Two sub 3
```

```html
<ul>
	<li>One</li>
	<li>Two
		<ul>
			<li>Two sub 1</li>
			<li>Two sub 2
				<ul>
					<li>Two sub 2 section A</li>
					<li>Two sub 2 section B</li>
				</ul>
			</li>
			<li>Two sub 3</li>
		</ul>
	</li>
</ul>
```

## List With Description
```gr
- First 
- Second 
- Third 
	+1 level indentation after current list will create the body of the list.
```

```html
<ul>
	<li>First</li>
	<li>Second</li>
	<li>Third
		<p>+1 level indentation after current list will create the body of the list.</p>
	</li>
</ul>
```

# Check List
```gr
[ ] To-do one 
[ ] To-do two
[x] Done three
[x] Done four
```

```html
<ol class="check-list">
	<li><input type="checkbox"> To-do one</li>
	<li><input type="checkbox"> To-do two</li>
	<li><input type="checkbox" checked> Done three</li>
	<li><input type="checkbox" checked> Done four</li>
</ol>
```

# Definition List
```gr
AP :: Appliances
AU :: Automotive
GA :: Garden shop
HB :: Health and beauty
HO :: Home decor
SP :: Sporting goods
```

```html
<dl>
	<dt>AP</dt> <dd>Appliances<dd>
	<dt>AU</dt> <dd>Automotive<dd>
	<dt>GA</dt> <dd>Garden shop<dd>
	<dt>HB</dt> <dd>Health and beauty<dd>
	<dt>HO</dt> <dd>Home decor<dd>
	<dt>SP</dt> <dd>Sporting goods<dd>
</dl>
```

```gr
CD Player Unit ::
	With auto-search, auto-off, power door,
	and a two-year warranty.
```

```html
<dl>
	<dt>CD Player Unit</dt> 
	<dd>
		<p>With auto-search, auto-off, power door,
		and a two-year warranty.</p>
	<dd>
</dl>
```

# Code
## Block Code
Anything between three or more dashes will be considered as code.
And make sure to have same dashes count between opening and ending.

### Anonymous Block
```gr
---
plain text or do fancy syntax detection here
---
```

```html
<pre><code>plain text or do fancy syntax detection here</code></pre>
```

### Labeled Block
```gr
--- cpp
#include <iostream>

int main() 
{
	std::cout << "Hello World\n";

	return 0;
}
---
```

```html
<pre><code class="language-cpp">#include <iostream>

int main() 
{
	std::cout &lt;&lt; "Hello World\n";

	return 0;
}</code></pre>
```

## Inline Code
### Anonymous Inline
```gr
Why do we use `console.log('here')` instead of the majestic breakpoint?
```

```html
<p>Why do we use <code>console.log('here')</code> instead of the majestic breakpoint?</p>
```

### Labeled Inline
```gr
Let's say `latex``\pi = 3` then the building is likely collapsed.
```

```html
<p>Let's say <code class="language-latex">\pi = 3</code> then the building is likely collapsed.</p>
```

# Table 
## Table Data Only
```gr
| 1 | 2 |
| 3 | 4 |
```

```html
<table>
	<tr>
		<td>1</td>
		<td>2</td>
	</tr>
	<tr>
		<td>3</td>
		<td>4</td>
	</tr>
</table>
```

## Table With Heading
```gr
| ID | Name   |
|----|--------|
|  1 | Name 1 |
|  2 | Name 2 |
```

```html
<table>
	<tr>
		<th>ID</th>
		<th>Name</th>
	</tr>
	<tr>
		<td>1</td>
		<td>Name 1</td>
	</tr>
	<tr>
		<td>2</td>
		<td>Name 2</td>
	</tr>
</table>
```

## Table With Heading And Alignment
```gr
| Left | Center | Right |
|:-----|:------:|------:|
| 1    |  Ada   |    19 |
| 2    | Fowler |    23 |
```

```html
<table>
	<tr>
		<th class="text-left">Left</th>
		<th class="text-left">Center</th>
		<th class="text-left">Right</th>
	</tr>
	<tr>
		<td class="text-center">1</td>
		<td class="text-center">Ada</td>
		<td class="text-center">19</td>
	</tr>
	<tr>
		<td class="text-right">2</td>
		<td class="text-right">Fowler</td>
		<td class="text-right">23</td>
	</tr>
</table>
```

## Table With Heading And Footer
Footer only works if the heading is defined.

```gr
| ID | Name   |
|----|--------|
|  1 | Name 1 |
|  2 | Name 2 |
|----|--------|
| ID | Name   |
```

```html
<table>
	<tr>
		<th>ID</th>
		<th>Name</th>
	</tr>
	<tr>
		<td>1</td>
		<td>Name 1</td>
	</tr>
	<tr>
		<td>2</td>
		<td>Name 2</td>
	</tr>
	<tr>
		<th>ID</th>
		<th>Name</th>
	</tr>
</table>
```

# Admonition
```gr
<Note> A note
<Hint> A hint
<Important> Important stuff
<Warning> Warning stuff
<See also> The Amazing Spiderman 2
<Tip> A tip
```

```html
<div class="admon note">
	<div class="label">Note</div>
	<div class="content">A note</div>
</div>
<div class="admon hint">
	<div class="label">Hint</div>
	<div class="content">a Hint</div>
</div>
<div class="admon important">
	<div class="label">Important</div>
	<div class="content">Important stuff</div>
</div>
<div class="admon warning">
	<div class="label">Warning</div>
	<div class="content">Warning sfuff</div>
</div>
<div class="admon see-also">
	<div class="label">See also</div>
	<div class="content">The Amazing Spiderman 2</div>
</div>
<div class="admon tip">
	<div class="label">Tip</div>
	<div class="content">A tip</div>
</div>
```

```gr
<Note>
	Long note.
	Very long note.
```

```html
<div class="admon">
	<div class="label">Note</div>
	<div class="content">
		<p>Long note.
		Very long note.</p>
	</div>
</div>
```

# Date‐Time
```gr
Diary <2018-05-10>

Met Sofia at <10:00> talked about her newborn child.
He said his first word today.
```

```html
<p>Diary <time datetime="2018-05-10">2018-05-10</time></p>

<p>Met Sofia at <time datetime="10:00">10:00</time> talked about her newborn child.
He said his first word today.</p>
```

# Tag
## Account Tag
```regex
@[A-Za-z0-9_]+
```

```gr
@MrAnderson
```

```html
<a class="account-tag" href="MrAnderson">@MrAnderson</a>
```

## Hash Tag
```regex
#[A-Za-z0-9_]+
```

```gr
#someTopic
```

```html
<a class="hash-tag" href="someTopic">#someTopic</a>
```

# Linker
## Net Link
```gr
[http://google.com]
```

```html
<p><a href="http://google.com">http://google.com</a></p>
```

### With Label
```gr
[http://google.com](Google)
```

```html
<p><a href="http://google.com">Google</a></p>
```

## Heading Link
```gr
[>Laminal Flow]
```

```html
<p><a href="#Laminar-Flow">Laminar Flow</a></p>
```

### With Label
```gr
[>Laminal Flow](see this segment)
```

```html
<p><a href="#Laminar-Flow">see this segment</a></p>
```

## Local Link
```gr
[Another Document.gr]
```

```html
<p><a href="Another Document.gr">Another Document</a></p>
```

### With Label
```gr
[Another Document.gr](see this document)
```

```html
<p><a href="Another Document.gr">see this document</a></p>
```

### With Specified Heading
```
[Another Document.gr>Legal Section]
```

```html
<p><a href="Another%20Document.gr#Legal-Section">Another Document Legal Section</a></p>
```

### With Specified Heading and Label
```
[Another Document.gr>Legal Section](see this section)
```

```html
<p><a href="Another%20Document.gr#Legal-Section">see this section</a></p>
```

# Viewer
Depends on the target ability to view the resource.
Like tsv can be presented as table or code block or a link to the resource.

## Block View
If the `View` is the only child of a `Paragraph` the view is promoted to block (The `Paragraph` node is removed)

## URL
```gr
![https://www.youtube.com/watch?v=dQw4w9WgXcQ]
```

## Assets
### Image
```gr
![cat.png]
```

```html
<img src="cat.png">
```

```gr
![cat.png](A cat)
```

```html
<figure>
	<img src="cat.png">
	<figcaption>A cat</figcaption>
</figure>
```

### Others
```gr
![mydata.tsv]
```

# Inclusion
Split the document into multiple files.

Only local files are allowed to be included.

```gr
?[chapter-1.gr]
?[chapter-2.gr]
```

# Citation
## In‐Text
```gr
^[12-rules] ^[lateral-thinking] ^[good-omens] ^[my-lady-jane]
```

```html
<p><a class="citation" href="#Reference-12-rules">(Peterson, 2018)</a>
<a class="citation" href="#Reference-lateral-thinking">(de Bono, 1970)</a>
<a class="citation" href="#Reference-good-omens">(Pratchett & Gaiman, 1990)</a>
<a class="citation" href="#Reference-my-lady-jane">(Hand et al., 2016)</a></p>
```

## References
```
^[12-rules]:
	title: 12 Rules of Life
	author: Jordan Bernt Peterson
	year: 2018
	publisher: Random House Canada

^[lateral-thinking]:
	title: Lateral Thinking: Creativity Step by Step
	author: Edward de Bono
	year: 1970
	publisher: Harper & Row

^[good-omens]:
	title: Good Omens: The Nice and Accurate Prophecies of Agnes Nutter, Witch
	authors: Terry Pratchett, Neil Gaiman
	year: 1990
	publisher: Gollancz 

^[my-lady-jane]:
	title: My Lady Jane
	authors: Cynthia Hand, Brodi Ashton, Jodi Meadows
	year: 2016
	publisher: HarperCollins
```

```html
<div class="reference" id="Reference-12-rules">Peterson, J.B., (2018). <i>12 Rules of Life</i>. Random House Canada.</div>
<div class="reference" id="Reference-lateral-thinking">de Bono, E., (1970). <i>Lateral Thinking: Creativity Step by Step</i>. Harper & Row.</div>
<div class="reference" id="Reference-good-omens">Pratchett, T. & Gaiman, N. (1990). <i>Good Omens: The Nice and Accurate Prophecies of Agnes Nutter, Witch</i>. Gollancz .</div>
<div class="reference" id="Reference-my-lady-jane">Hand, C., Ashton, B. & Meadows, J. (2016). <i>My Lady Jane</i>. HarperCollins.</div>
```

# Footnote
Footnote description automatically injected in the correct page.

In html footnote should be included before page break or heading.

```gr 
Here's a simple footnote,^(This is the first footnote.) and here's a another one.^(Very important part)
```

```html
<p>Here's a simple footnote,<sup><a href="Footnote-1">1</a></sup>
and here's a another one.<sup><a href="Footnote-2">2</a></sup></p>

<div class="footnote-desc">
	<p><sup>1</sup> This is the first footnote.</p>
	<p><sup>2</sup> Very important part</p>
</div>
```

# Punctuation
## Quotation
Any single or double apostrophe will be converted into the correct left and right quotes.

```gr
"Don't you dare!" He said calmly.
```

```html
<p>&#8223;Don&#8217;t you dare!&#8221; He said calmly.</p>
```

## Hyphen, En Dash, Em Dash
Two hyphen will make en dash.
Three hyphen will make em dash.

```gr
A closed-door meetings
I’ll schedule you from 4:30--5:00
Wait! I forgot to tell you---
```

```html
<p>A closed&#8208;door meetings
I’ll schedule you from 4:30&#8211;5:00
Wait! I forgot to tell you&#8212;</p>
```

# Emoji
```regex
:[a-z-]+:
```

```gr
I look forward to see you soon :smile:!

:coffee:
```

```html
<p>I look forward to see you soon <span class="emoji">smile</span>!</p>

<p><span class="emoji">coffee</span>
```

## Expression
smile: 😄,
small‐smile: 🙂,
laughing: 😆,
blush: 😊,
smiley: 😃,
relaxed: ☺️,
smirk: 😏,
heart‐eyes: 😍,
kissing‐heart: 😘,
kissing‐closed‐eyes: 😚,
flushed: 😳,
relieved: 😌,
satisfied: 😆,
grin: 😁,
wink: 😉,
stuck‐out‐tongue‐winking‐eye: 😜,
stuck‐out‐tongue‐closed‐eyes: 😝,
grinning: 😀,
kissing: 😗,
kissing‐smiling‐eyes: 😙,
stuck‐out‐tongue: 😛,
sleeping: 😴,
worried: 😟,
frowning: 😦,
anguished: 😧,
open‐mouth: 😮,
grimacing: 😬,
confused: 😕,
hushed: 😯,
expressionless: 😑,
unamused: 😒,
sweat‐smile: 😅,
sweat: 😓,
disappointed‐relieved: 😥,
weary: 😩,
pensive: 😔,
disappointed: 😞,
confounded: 😖,
fearful: 😨,
cold‐sweat: 😰,
persevere: 😣,
cry: 😢,
sob: 😭,
joy: 😂,
astonished: 😲,
scream: 😱,
tired‐face: 😫,
angry: 😠,
rage: 😡,
triumph: 😤,
sleepy: 😪,
yum: 😋,
mask: 😷,
sunglasses: 😎,
dizzy‐face: 😵,
imp: 👿,
smiling‐imp: 😈,
neutral‐face: 😐,
no‐mouth: 😶,
innocent: 😇,
alien: 👽,
yellow‐heart: 💛,
blue‐heart: 💙,
purple‐heart: 💜,
heart: ❤️,
green‐heart: 💚,
broken‐heart: 💔,
heartbeat: 💓,
heartpulse: 💗,
two‐hearts: 💕,
revolving‐hearts: 💞,
cupid: 💘,
sparkling‐heart: 💖,
sparkles: ✨,
star: ⭐,
shining‐star: 🌟,
dizzy: 💫,
boom: 💥,
collision: 💥,
anger: 💢,
exclamation: ❗,
question: ❓,
grey‐exclamation: ❕,
grey‐question: ❔,
zzz: 💤,
dash: 💨,
sweat‐drops: 💦,
notes: 🎶,
musical‐note: 🎵,
fire: 🔥,
hankey: 💩,
poop: 💩,
shit: 💩,
thumbsup: 👍,
thumbsdown: 👎,
ok‐hand: 👌,
punch: 👊,
facepunch: 👊,
fist: ✊,
two‐fingers: ✌️,
one‐finger: ☝️,
wave: 👋,
hand: ✋,
raised‐hand: ✋,
open‐hands: 👐,
point‐down: 👇,
point‐left: 👈,
point‐right: 👉,
raised‐hands: 🙌,
pray: 🙏,
point‐up: 👆,
clap: 👏,
muscle: 💪,
metal: 🤘,
fu: 🖕,
walking: 🚶,
runner: 🏃,
running: 🏃,
couple: 👫,
family: 👪,
two‐men‐holding‐hands: 👬,
two‐women‐holding‐hands: 👭,
dancer: 💃,
dancers: 👯,
ok‐woman: 🙆‍♀️,
no‐good: 🙅,
information‐desk‐person: 💁,
raising‐hand: 🙋,
bride‐with‐veil: 👰‍♀️,
bow: 🙇,
couplekiss: 💏,
couple‐with‐heart: 💑,
massage: 💆,
haircut: 💇,
nail‐care: 💅,
boy: 👦,
girl: 👧,
woman: 👩,
man: 👨,
baby: 👶,
older‐woman: 👵,
older‐man: 👴,
man‐with‐gua‐pi‐mao: 👲,
man‐with‐turban: 👳‍♂️,
construction‐worker: 👷,
cop: 👮,
angel: 👼,
princess: 👸,
smiley‐cat: 😺,
smile‐cat: 😸,
heart‐eyes‐cat: 😻,
kissing‐cat: 😽,
smirk‐cat: 😼,
scream‐cat: 🙀,
crying‐cat‐face: 😿,
joy‐cat: 😹,
pouting‐cat: 😾,
japanese‐ogre: 👹,
japanese‐goblin: 👺,
see‐no‐evil: 🙈,
hear‐no‐evil: 🙉,
speak‐no‐evil: 🙊,
guardsman: 💂‍♂️,
skull: 💀,
feet: 🐾,
lips: 👄,
kiss: 💋,
droplet: 💧,
ear: 👂,
eye: 👁️,
eyes: 👀,
nose: 👃,
tongue: 👅,
love‐letter: 💌,
bust‐in‐silhouette: 👤,
busts‐in‐silhouette: 👥,
speech‐balloon: 💬,
thought‐balloon: 💭,

## Nature
sun: ☀️,
sunny: ☀️,
umbrella: ☔,
cloud: ☁️,
rainy: 🌧️,
snowflake: ❄️,
snowman: ⛄,
zap: ⚡,
cyclone: 🌀,
foggy: 🌁,
ocean: 🌊,
cat‐face: 🐱,
dog‐face: 🐶,
mouse‐face: 🐭,
hamster‐face: 🐹,
rabbit‐face: 🐰,
wolf‐face: 🐺,
frog‐face: 🐸,
tiger‐face: 🐯,
koala‐face: 🐨,
bear‐face: 🐻,
pig‐face: 🐷,
pig‐nose: 🐽,
cow‐face: 🐮,
boar‐face: 🐗,
monkey‐face: 🐵,
monkey: 🐒,
horse‐face: 🐴,
racehorse: 🐎,
camel: 🐫,
sheep: 🐑,
elephant: 🐘,
panda‐face: 🐼,
snake: 🐍,
bird‐face: 🐦,
baby‐chick‐face: 🐤,
hatched‐chick: 🐥,
hatching‐chick: 🐣,
chicken‐face: 🐔,
penguin‐face: 🐧,
turtle: 🐢,
bug: 🐛,
honeybee: 🐝,
ant: 🐜,
beetle: 🪲,
snail: 🐌,
octopus: 🐙,
tropical‐fish: 🐠,
fish: 🐟,
spouting‐whale: 🐳,
whale: 🐋,
dolphin: 🐬,
cow: 🐄,
ram: 🐏,
rat: 🐀,
water‐buffalo: 🐃,
tiger: 🐅,
rabbit: 🐇,
dragon: 🐉,
goat: 🐐,
rooster: 🐓,
dog: 🐕,
pig: 🐖,
mouse: 🐁,
ox: 🐂,
dragon‐face: 🐲,
blowfish: 🐡,
crocodile: 🐊,
dromedary‐camel: 🐪,
leopard: 🐆,
cat: 🐈,
poodle: 🐩,
paw‐prints: 🐾,
bouquet: 💐,
cherry‐blossom: 🌸,
tulip: 🌷,
four‐leaf‐clover: 🍀,
rose: 🌹,
sunflower: 🌻,
hibiscus: 🌺,
maple‐leaf: 🍁,
leaves: 🍃,
fallen‐leaf: 🍂,
herb: 🌿,
mushroom: 🍄,
cactus: 🌵,
palm‐tree: 🌴,
evergreen‐tree: 🌲,
deciduous‐tree: 🌳,
chestnut: 🌰,
seedling: 🌱,
blossom: 🌼,
ear‐of‐rice: 🌾,
shell: 🐚,
globe‐with‐meridians: 🌐,
sun‐with‐face: 🌞,
full‐moon‐with‐face: 🌝,
new‐moon‐with‐face: 🌚,
new‐moon: 🌑,
waxing‐crescent‐moon: 🌒,
first‐quarter‐moon: 🌓,
waxing‐gibbous‐moon: 🌔,
full‐moon: 🌕,
waning‐gibbous‐moon: 🌖,
last‐quarter‐moon: 🌗,
waning‐crescent‐moon: 🌘,
last‐quarter‐moon‐with‐face: 🌜,
first‐quarter‐moon‐with‐face: 🌛,
moon: 🌔,
earth‐africa: 🌍,
earth‐americas: 🌎,
earth‐asia: 🌏,
volcano: 🌋,
milky‐way: 🌌,
partly‐sunny: ⛅,

## Objects
bamboo: 🎍,
gift‐heart: 💝,
dolls: 🎎,
school‐satchel: 🎒,
mortar‐board: 🎓,
flags: 🎏,
fireworks: 🎆,
sparkler: 🎇,
wind‐chime: 🎐,
rice‐scene: 🎑,
jack‐o‐lantern: 🎃,
ghost: 👻,
santa: 🎅,
christmas‐tree: 🎄,
gift: 🎁,
bell: 🔔,
no‐bell: 🔕,
tanabata‐tree: 🎋,
tada: 🎉,
confetti‐ball: 🎊,
balloon: 🎈,
crystal‐ball: 🔮,
cd: 💿,
dvd: 📀,
floppy‐disk: 💾,
camera: 📷,
video‐camera: 📹,
movie‐camera: 🎥,
computer: 💻,
tv: 📺,
iphone: 📱,
telephone: ☎️,
telephone‐receiver: 📞,
pager: 📟,
fax: 📠,
minidisc: 💽,
vhs: 📼,
sound: 🔉,
speaker: 🔈,
mute: 🔇,
loudspeaker: 📢,
mega: 📣,
hourglass: ⌛,
hourglass‐flowing‐sand: ⏳,
alarm‐clock: ⏰,
watch: ⌚,
radio: 📻,
satellite: 📡,
loop: ➿,
mag: 🔍,
mag‐right: 🔎,
unlock: 🔓,
lock: 🔒,
lock‐with‐ink‐pen: 🔏,
closed‐lock‐with‐key: 🔐,
key: 🔑,
bulb: 💡,
flashlight: 🔦,
high‐brightness: 🔆,
low‐brightness: 🔅,
electric‐plug: 🔌,
battery: 🔋,
calling: 📲,
email: 📧,
mailbox: 📫,
postbox: 📮,
bath: 🛀,
bathtub: 🛁,
shower: 🚿,
toilet: 🚽,
wrench: 🔧,
nut‐and‐bolt: 🔩,
hammer: 🔨,
seat: 💺,
moneybag: 💰,
yen: 💴,
dollar: 💵,
pound: 💷,
euro: 💶,
credit‐card: 💳,
money‐with‐wings: 💸,
e‐mail: 📧,
inbox‐tray: 📥,
outbox‐tray: 📤,
envelope: ✉️,
incoming‐envelope: 📨,
postal‐horn: 📯,
mailbox‐closed: 📪,
mailbox‐with‐mail: 📬,
mailbox‐with‐no‐mail: 📭,
door: 🚪,
smoking: 🚬,
bomb: 💣,
gun: 🔫,
hocho: 🔪,
pill: 💊,
syringe: 💉,
page‐facing‐up: 📄,
page‐with‐curl: 📃,
bookmark‐tabs: 📑,
bar‐chart: 📊,
chart‐with‐upwards‐trend: 📈,
chart‐with‐downwards‐trend: 📉,
scroll: 📜,
clipboard: 📋,
calendar: 📆,
date: 📅,
card‐index: 📇,
file‐folder: 📁,
open‐file‐folder: 📂,
scissors: ✂️,
pushpin: 📌,
paperclip: 📎,
black‐nib: ✒️,
pencil: ✏️,
straight‐ruler: 📏,
triangular‐ruler: 📐,
closed‐book: 📕,
green‐book: 📗,
blue‐book: 📘,
orange‐book: 📙,
notebook: 📓,
notebook‐with‐decorative‐cover: 📔,
ledger: 📒,
books: 📚,
bookmark: 🔖,
name‐badge: 📛,
microscope: 🔬,

telescope: 🔭,
newspaper: 📰,
football: 🏈,
basketball: 🏀,
soccer: ⚽,
baseball: ⚾,
tennis: 🎾,
eight‐ball: 🎱,
rugby‐football: 🏉,
bowling: 🎳,
golf: ⛳,
mountain‐bicyclist: 🚵,
bicyclist: 🚴,
horse‐racing: 🏇,
snowboarder: 🏂,
swimmer: 🏊,
surfer: 🏄,
ski: 🎿,
spades: ♠️,
hearts: ♥️,
clubs: ♣️,
diamonds: ♦️,
gem: 💎,
ring: 💍,
trophy: 🏆,
musical‐score: 🎼,
musical‐keyboard: 🎹,
violin: 🎻,
space‐invader: 👾,
video‐game: 🎮,
black‐joker: 🃏,
flower‐playing‐cards: 🎴,
game‐die: 🎲,
dart: 🎯,
mahjong: 🀄,
clapper: 🎬,
memo: 📝,
book: 📖,
art: 🎨,
microphone: 🎤,
headphones: 🎧,
trumpet: 🎺,
saxophone: 🎷,
guitar: 🎸,
shoe: 👞,
sandal: 👡,
high‐heel: 👠,
lipstick: 💄,
boot: 👢,
shirt: 👕,
tshirt: 👕,
necktie: 👔,
womans‐clothes: 👚,
dress: 👗,
running‐shirt‐with‐sash: 🎽,
jeans: 👖,
kimono: 👘,
bikini: 👙,
ribbon: 🎀,
tophat: 🎩,
crown: 👑,
womans‐hat: 👒,
mans‐shoe: 👞,
closed‐umbrella: 🌂,
briefcase: 💼,
handbag: 👜,
pouch: 👝,
purse: 👛,
glasses: 👓,
fishing‐pole‐and‐fish: 🎣,
coffee: ☕,
tea: 🍵,
sake: 🍶,
baby‐bottle: 🍼,
beer: 🍺,
beers: 🍻,
cocktail: 🍸,
tropical‐drink: 🍹,
wine‐glass: 🍷,
fork‐and‐knife: 🍴,
pizza: 🍕,
hamburger: 🍔,
fries: 🍟,
poultry‐leg: 🍗,
meat‐on‐bone: 🍖,
spaghetti: 🍝,
curry: 🍛,
fried‐shrimp: 🍤,
bento: 🍱,
sushi: 🍣,
fish‐cake: 🍥,
rice‐ball: 🍙,
rice‐cracker: 🍘,
rice: 🍚,
ramen: 🍜,
stew: 🍲,
oden: 🍢,
dango: 🍡,
egg: 🥚,
bread: 🍞,
doughnut: 🍩,
custard: 🍮,
icecream: 🍦,
ice‐cream: 🍨,
shaved‐ice: 🍧,
birthday: 🎂,
cake: 🍰,
cookie: 🍪,
chocolate‐bar: 🍫,
candy: 🍬,
lollipop: 🍭,
honey‐pot: 🍯,
apple: 🍎,
green‐apple: 🍏,
tangerine: 🍊,
lemon: 🍋,
cherries: 🍒,
grapes: 🍇,
watermelon: 🍉,
strawberry: 🍓,
peach: 🍑,
melon: 🍈,
banana: 🍌,
pear: 🍐,
pineapple: 🍍,
sweet‐potato: 🍠,
eggplant: 🍆,
tomato: 🍅,
corn: 🌽,

## Places
house: 🏠,
house‐with‐garden: 🏡,
school: 🏫,
office: 🏢,
post‐office: 🏣,
hospital: 🏥,
bank: 🏦,
convenience‐store: 🏪,
love‐hotel: 🏩,
hotel: 🏨,
wedding: 💒,
church: ⛪,
department‐store: 🏬,
european‐post‐office: 🏤,
city‐sunrise: 🌇,
city‐sunset: 🌆,
japanese‐castle: 🏯,
european‐castle: 🏰,
tent: ⛺,
factory: 🏭,
tokyo‐tower: 🗼,
japan: 🗾,
mount‐fuji: 🗻,
sunrise‐over‐mountains: 🌄,
sunrise: 🌅,
stars: 🌠,
statue‐of‐liberty: 🗽,
bridge‐at‐night: 🌉,
carousel‐horse: 🎠,
rainbow: 🌈,
ferris‐wheel: 🎡,
fountain: ⛲,
roller‐coaster: 🎢,
ship: 🚢,
speedboat: 🚤,
boat: ⛵,
sailboat: ⛵,
rowboat: 🚣,
anchor: ⚓,
rocket: 🚀,
airplane: ✈️,
helicopter: 🚁,
steam‐locomotive: 🚂,
tram: 🚊,
mountain‐railway: 🚞,
bike: 🚲,
aerial‐tramway: 🚡,
suspension‐railway: 🚟,
mountain‐cableway: 🚠,
tractor: 🚜,
blue‐car: 🚙,
oncoming‐automobile: 🚘,
car: 🚗,
red‐car: 🚗,
taxi: 🚕,
oncoming‐taxi: 🚖,
articulated‐lorry: 🚛,
bus: 🚌,
oncoming‐bus: 🚍,
rotating‐light: 🚨,
police‐car: 🚓,
oncoming‐police‐car: 🚔,
fire‐engine: 🚒,
ambulance: 🚑,
minibus: 🚐,
truck: 🚚,
railway‐car: 🚋,
station: 🚉,
train: 🚆,
bullettrain‐front: 🚅,
bullettrain‐side: 🚄,
light‐rail: 🚈,
monorail: 🚝,
railway‐car: 🚃,
trolleybus: 🚎,
ticket: 🎫,
fuelpump: ⛽,
vertical‐traffic‐light: 🚦,
traffic‐light: 🚥,
warning: ⚠️,
construction: 🚧,
beginner: 🔰,
atm: 🏧,
slot‐machine: 🎰,
busstop: 🚏,
barber: 💈,
hotsprings: ♨️,
checkered‐flag: 🏁,
crossed‐flags: 🎌,
izakaya‐lantern: 🏮,
moyai: 🗿,
circus‐tent: 🎪,
performing‐arts: 🎭,
round‐pushpin: 📍,

