#include <vector>
#include <memory>
#include <iostream>
using namespace std;


class CWidget
{
public:
	virtual void paint() = 0;
};

class CWindowsButton : public CWidget
{
public:
	void paint()
	{
		cout << "drawing windows button" << endl;
	}
};

class CMacButton : public CWidget
{
public:
	void paint()
	{
		cout << "drawing Mac button" << endl;
	}
};

class CWindowsCheckBox : public CWidget
{
public:
	void paint()
	{
		cout << "drawing windows check box" << endl;
	}
};

class CMacCheckBox : public CWidget
{
public:
	void paint()
	{
		cout << "drawing mac check box" << endl;
	}
};

class CWidgetFactory
{
public:
	virtual CWidget* createButton() = 0;
	virtual CWidget* createCheckBox() = 0;
};

class CWindowsFactory : public CWidgetFactory
{
public:
	CWidget* createButton()
	{
		return new CWindowsButton;
	}

	CWidget* createCheckBox()
	{
		return new CWindowsCheckBox;
	}
};

class CMacFactory : public CWidgetFactory
{
	CWidget* createButton()
	{
		return new CMacButton;
	}

	CWidget* createCheckBox()
	{
		return new CMacCheckBox;
	}
};


class CClient
{
	
private:
	std::unique_ptr<CWidgetFactory> m_pFactory;
	std::vector<std::unique_ptr<CWidget>> widgets;

public:
	CClient(CWidgetFactory* pFactory) : m_pFactory(pFactory)
	{

	}

	void createWindow()
	{
		widgets.push_back(std::unique_ptr<CWidget>(m_pFactory->createButton()));
		widgets.push_back(std::unique_ptr<CWidget>(m_pFactory->createCheckBox()));
	}

	void Draw()
	{
		for (auto i=0 ; i<widgets.size(); ++i)
		{
			widgets[i]->paint();
		}
	}
};