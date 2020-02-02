const char* names[] = { "epub","pdf","mobi" };

enum Format { EPUB, PDF, MOBI };



class Book
{
private:

    Format format;

public:

	Book(Format format)
	{
		this->format = format;
	}

	Format getFormat()
	{
		return format;
	}
};

class EBookReader
{
protected:
	Book *book;

public:

	EBookReader(Book *b)
	{
		this->book = b;
	}

	virtual string readBook() = 0;
	virtual string displayReaderType() = 0;
};



class EpubReader :public EBookReader
{
public:

	EpubReader(Book *b):EBookReader(b){}

	string readBook()
	{
		return names[book->getFormat()];
	}

	string displayReaderType()
	{
		return "Using EPUB reader";
	}
};

class MobiReader :public EBookReader
{
public:

	MobiReader(Book *b):EBookReader(b){}

	string readBook()
	{
		return names[book->getFormat()];
	}

	string displayReaderType()
	{
		return "Using MOBI reader";
	}
};

class PdfReader :public EBookReader
{
public:

	PdfReader(Book *b):EBookReader(b){}

	string readBook()
	{
		return names[book->getFormat()];
	}

	string displayReaderType()
	{
		return "Using PDF reader";
	}
};

class EBookReaderFactory
{
public:

	EBookReader *createReader(Book *b)
	{
		if (b->getFormat() == EPUB)
		{
			return new EpubReader(b);
		}
		else if (b->getFormat() == MOBI)
		{
			return new MobiReader(b);
		}
		else if (b->getFormat() == PDF)
		{
			return new PdfReader(b);
		}
		else
		{
			return NULL;
		}
	}
};

class Kindle
{
private:

	vector<Book *> *books;
	EBookReaderFactory *readerFactory;

public:

	Kindle()
	{
		books = new vector<Book *>;
		readerFactory = new EBookReaderFactory;
	}

	string readBook(Book *book)
	{
		EBookReader *reader = readerFactory->createReader(book);
		return reader->displayReaderType() + ", book content is: " + reader->readBook();
	}

	void downloadBook(Book *b)
	{
		books->push_back(b);
	}

	void uploadBook(Book *b)
	{
		books->push_back(b);
	}

	void deleteBook(Book *b)
	{
		vector<Book *>::iterator it;
		for (it = books->begin(); it != books->end(); it++)
		{
			if ((*it)->getFormat() == b->getFormat())
			{
				books->erase(it);
				return;
			}
		}
	}
};