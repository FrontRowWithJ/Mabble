#include "TextBox.hpp"

TextBox::TextBox(float _xPos, float _yPos, float _width, float _height, float _raidus, const char*fontName, const char *_message, Color _bgColor, Color _textColor)
{
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    this->fontName = fontName;
    message = _message;
    bgColor = _bgColor;
    textColor = _textColor;
    background = RoundedRectangle(xPos, yPos, width, height, _raidus, 7);
    background.set_fill_color(bgColor);
}

void TextBox::draw(RenderWindow *window)
{
    background.draw(window);
    for (int i = 0; i < textLen; i++)
        window->draw(boxText[i]);
}

void TextBox::gen_text()
{
    LinkedList<char *> tokens = LinkedList<char *>();
    size_t messageLen = strlen(message);
    char *buf = new char();
    int messageIndex = 0;
    while (message[messageIndex++] == ' ')
        ;
    for (int i = messageIndex - 1; i < messageLen; i++)
    {
        if (message[i] != ' ')
            add_char(buf, message[i]);
        else
        {
            add_char(buf, ' ');
            tokens.insert(buf);
            buf = new char();
        }
    }
    LinkedList<Text> textList = LinkedList<Text>();
    tokens.insert(buf);
    int charSize = 30;
    float stringWidth = 0;
    string line = string();
    for (LinkedList<char *>::Node *node = tokens.head; node != NULL; node = node->next)
    {
        Font f;
        f.loadFromFile(fontName);
        Text t(node->val, f, charSize);
        FloatRect lb = t.getLocalBounds();
        if (stringWidth + lb.width <= width)
        {
            line += node->val;
            stringWidth += lb.width;
        }
        else
        {
            textList.insert(Text(line, f, charSize));
            line = node->val;
            stringWidth = lb.width;
            textLen++;
        }
    }
    Font f;
    f.loadFromFile(fontName);
    Text t(line, f, charSize);
    textList.insert(t);
    textLen++;
    boxText = new Text[textLen];
    int i = 0;
    for (LinkedList<Text>::Node *node = textList.head; node != NULL; node = node->next)
    {
        boxText[i] = node->val;
        FloatRect lb = boxText[i].getLocalBounds();
        Font f;
        f.loadFromFile(fontName);
        boxText[i].setFont(f);
        boxText[i].setOrigin(lb.left, lb.top);
        boxText[i].setFillColor(textColor);
        string str = boxText[i].getString();
        if (str.c_str()[str.length() - 1] == ' ')
            boxText[i].setString(str.substr(0, str.length() - 1));
        i++;
    }
}

void TextBox::add_char(char *&str, char c)
{
    int strLen = strlen(str);
    str = static_cast<char *>(realloc(str, strLen + 2));
    str[strLen] = c;
    str[strLen + 1] = '\0';
}

void TextBox::set_textStyle(TextStyle horizontal, TextStyle vertical)
{
    this->vertical = vertical;
    this->horizontal = horizontal;
    float top = 0.f, offset = 0.f;
    for (int i = 0; i < textLen; i++)
        top += boxText[i].getLocalBounds().height;
    top = (height - top) / 2.f;
    for (int i = 0; i < textLen; i++)
    {
        FloatRect lb = boxText[i].getLocalBounds();
        boxText[i].setPosition(xPos + (int)horizontal * ((width - lb.width) / 2), yPos + ((int)vertical - 3) * top + offset);
        offset += lb.height;
    }
}

void TextBox::set_color(Color textColor, Color bgColor)
{
    this->textColor = textColor;
    this->bgColor = bgColor;
    for (int i = 0; i < textLen; i++)
        boxText[i].setFillColor(bgColor);
    background.set_fill_color(bgColor);
}

Color TextBox::get_bgColor()
{
    return bgColor;
}

Color TextBox::get_textColor()
{
    return textColor;
}

void TextBox::set_characterSize(int characterSize)
{
    for (int i = 0; i < textLen; i++)
        boxText[i].setCharacterSize(characterSize);
}

void TextBox::fit_to_text()
{
    float newWidth = 0;
    float newHeight = 0;
    Vector2f newPos = boxText->getPosition();
    for (int i = 0; i < textLen; i++)
    {
        FloatRect lb = boxText[i].getLocalBounds();
        newWidth = max(newWidth, lb.width);
        newHeight += lb.height;
    }
    width = newWidth;
    height = newHeight;
    xPos = newPos.x;
    yPos = newPos.y;
    background.set_size(width, height);
    background.set_position(newPos.x, newPos.y);
}