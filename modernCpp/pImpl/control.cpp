#include <string>
#include <iostream>

class CtrlImpl
{

	std::string _text;
	int _width = 0;
	int _height = 0;

	bool _visible = true;


	void Draw()
	{
		std::cout
				<< "control " << std::endl
				<< " visible: " << std::boolalpha << _visible << noboolalpha << std::endl
				<< " size: " << _width << ", " << _height << std::endl
				<< " text: " << _text << std::endl;
	}

public: 
	void SetText(std::string_view t)
	{
		text = t.data();
		Draw();
	}

	void Resize(int const w, int const h)
	{
		_width = w;
		_height = h;
		Draw();
	}

	void Show()
	{
		_visible = true;
		Draw();
	}

	void Hide()
	{
		_visible = false;
		Draw();
	}

};

class Control
{

	std::unique_ptr<CtrlImpl, void(*) (CtrlImpl *)> pImpl;

public:

	Control() : pImpl(new CtrlImpl(), [](CtrlImpl *pImpl) {delete pImpl;}) {}

	void SetText(std::string_view text)
	{
		pImpl->SetText(text);
	}

	Resize(int const w, int const h)
	{
		pImpl->Resize(w, h);
	}

	Show()
	{
		pImpl->Show();
	}

	Hide()
	{
		pImpl->Hide();
	}
};