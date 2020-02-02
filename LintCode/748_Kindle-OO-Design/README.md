748. Kindle OO Design
中文English
Design Kindle, which can support 3 type of book format: PDF, MOBI and EPUB.

Consider using ENUM for book format.
Consider using simple factory to create reader for each format.
Example
Input:

readBook("EPUB")
readBook("PDF")
readBook("MOBI")
Output:

Using EPUB reader, book content is: epub
Using PDF reader, book content is: pdf
Using MOBI reader, book content is: mobi
