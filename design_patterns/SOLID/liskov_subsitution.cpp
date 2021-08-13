#include <iostream>

class Rectangle
{
protected:
	int mWidth, mHeight;
public:
	Rectangle(int width, int height) : mWidth(width), mHeight(height) {};
	int GetWidth() const {
		return mWidth;
	}
	int GetHeigh() const {
		return mHeight;
	}
	virtual void SetWidth(int width) {
		mWidth = width;
	}
	virtual void SetHeight(int height) {
		mHeight = height;
	}
	int Area() const {return mWidth * mHeight;}


};

class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size) {};
	void SetWidth(int width) override {
		mWidth = mHeight = width;
	}
	void SetHeight(int height) override {
		mHeight = mWidth = height;
	}

};

void Process(Rectangle& rect)
{
	int w = rect.GetWidth();
	rect.SetHeight(10);
	std::cout << "Expected area = " << (w * 10)
			  << ", got " << rect.Area() << std::endl;
}

int main()
{
	Rectangle aRect{3, 4};
	Process(aRect);

	Square aSquare{5};
	Process(aSquare);

	return 0;
}