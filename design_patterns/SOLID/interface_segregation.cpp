#include <iostream>

struct Document;

struct IMachine
{
	virtual void Print(Document& doc) = 0;
	virtual void Scan(Document& doc) = 0;
	virtual void Fax(Document& doc) = 0;
}

struct Printer : IMachine
{
	void Print(Document& doc) override {
		// oke
	}
	void Scan(Document& doc) override {
		// not oke
	}
	void Fax(Document& doc) override {
		// not oke
	}
}

// Need to separate interface

struct IPrinter
{
	virtual Print(Document& doc) = 0;
}
struct IScanner
{
	virtual Scan(Document& doc) = 0;
}
struct IFax
{
	virtual Fax(Document& doc) = 0;
}

// combine two machines
struct IPrintAndScan : IPrinter, IScanner {};
struct Machine : IPrintAndScan
{
	IPrinter& mPrinter;
	IScanner& mScanner;
	Machine(IPrinter& printer, IScanner& scanner)
			: mPrinter(printer)
			, mScanner(scanner) {}

};

int main()
{


	return 0;
}