# Gularen
A sweet-spot of markup language

## Overview
<img width="1426" alt="Screenshot 2024-03-05 at 17 26 30" src="https://github.com/noorwachid/gularen/assets/42460975/d90f21f9-12e0-4d91-ab1e-23e29d9911c8">

## Live Demo
[Right over here](https://noorwach.id/gularen/editor/)

## CLI
[Right over there](cli/readme.md)

## Contributors
[Please read](contributor.md)

## Editor Support
- [VS Code](https://marketplace.visualstudio.com/items?itemName=nwachid.gularen)
- [Vim](https://github.com/noorwachid/vim-gularen)
- [Tree Sitter](https://github.com/noorwachid/tree-sitter-gularen)

## Why Not Use Markdown?
**Shorter**, create bold text with a single asterisk: `*bold*`.

**Consistency**, Every expression of Gularen only perform one action, and there is no alternative syntax.

**Better order and default**, In the image expression, the URL is the first argument `![https://i.imgflip.com/7r6vdk.jpg]`. You don't even have to write the label.

**Comment**, Anything after `~` in `now you see me ~ now you don't` will not be rendered.

**Secure**, You dont have to worry about inline HTML, because Gularen does not support inline HTML.

I drew most of my inspiration from AsciiDoc and Markdown, so there aren't any drastic changes to the syntax and structures.

## Specification and Examples
[Right over here](https://noorwach.id/gularen/spec.html)

## Changelog
**DATE MERGED**
New features:
- Highlight:
  Highlight syntax: `=highlighted sentence.=`

- Tag:
  - Account tag syntax: `@mention`
  - Hash tag sytax: `#someTopic`

- Annotation:
  - Annotation syntax: `~~ key: value`

- Citation
  - Citation style configuration (with annotation): `~~ citation-style: apa`
  - Citation syntax: `^[title-year]`
  - Reference syntax: 
    ```
    ^[title-year]:
      title: Some Book,
      author: Some Author,
      year: 2001
    ```
- Definition list:
  Definition syntax: `Stocks :: 10 pcs`

Breaking changes:
- Footnote syntax:
  From `^[1]` with `=[1] description` to `^(description)`
  Numbering is autogenerated and placed in the correct page (PDF and page based document)
- Inline code
  - Anonymous syntax: `console.log('hello world')`
  - Labeled syntax: `js``console.log('hello world')`
- Monospaced style is removed

**2024-03-01**:

Breaking changes:
- Admonition label will be writen as is

**2024-02-29**:
Breaking changes:
- Removing heading ID `Heading > ID`

**2023-08-05**:

New features:
- Date-time marker:
    - Date: `<2018-06-12>`
    - Time: `<10:00>` or `<10:00:12>`
    - Date-time: `<2018-06-12 10:00>` or `<2018-06-12 10:00:12>`

Breaking changes:
- Line-break syntax: from `<` into `<<`.
- Page-break syntax: from `<<` into `<<<`.
- Admonition syntax:
    - Tip: from `<+>` to `<tip>`.
    - Note: from `</>` to `<note>`.
    - Hint: from `<?>` to `<hint>`.
    - Reference: from `<&>` to `<reference>`.
    - Important: from `<!>` to `<important>`.
    - Warning: from `<^>` to `<warning>`.


