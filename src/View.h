#ifndef VIEW_H
#define VIEW_H


class View
{
public:
    virtual ~View(){}
    virtual void update() = 0;
};

class TextualView : public View {
public:
    ~TextualView(){}
    virtual void update(){
    }
};

#endif // VIEW_H
