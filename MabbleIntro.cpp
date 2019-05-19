#include "MabbleIntro.hpp"

MabbleIntro::MabbleIntro(float xPos, float yPos, float gap, float iconWidth, float iconHeight, float iconRadius, Color bgColor, Color textColor, Font font)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->gap = gap;
    this->iconWidth = iconWidth;
    this->iconHeight = iconHeight;
    this->iconRadius = iconRadius;
    this->bgColor = bgColor;
    this->fgColor = Color::Black;
    this->textColor = textColor;
    this->font = font;
    this->logo = "MABBLE";
    this->numberOfIcons = this->logo.length();
    this->seconds = 0.f;
    this->isFading = false;
    this->yOffset = 0.0f;
    this->amplitude = 30;
    this->baseY = new float[numberOfIcons];
    this->f = NEITHER;
    this->movement = NONE;
    this->canMoveStraight = new bool[numberOfIcons + 1];
    this->canMoveStraight[numberOfIcons] = true;
    this->cycle = new int[numberOfIcons];
    gen_icon_box();
    gen_icon_text();
}

void MabbleIntro::gen_icon_box()
{
    icons = new RoundedRectangle[numberOfIcons];
    float xOffset = 0;
    float yOffset = M_PI_2;
    for (int i = 0; i < numberOfIcons; i++)
    {
        baseY[i] = yOffset;
        cycle[i] = static_cast<int>(baseY[i] / OFFSET);
        icons[i] = RoundedRectangle(xPos + xOffset, yPos + amplitude * sin(baseY[i]), iconWidth, iconHeight, iconRadius, iconRadius, iconRadius, iconRadius, 10);
        xOffset += iconWidth + gap;
        icons[i].set_fill_color(fgColor);
        icons[i].set_outline_color(bgColor);
        icons[i].gen_shadow(5.f);
        yOffset += M_PI / (float)numberOfIcons;
    }
}

void MabbleIntro::gen_icon_text()
{
    iconText = new Text[numberOfIcons];
    for (int i = 0; i < numberOfIcons; i++)
    {
        iconText[i] = Text(new char[2]{logo[i], '\0'}, font);
        set_text_position(&iconText[i], &icons[i]);
        iconText[i].setFillColor(textColor);
    }
}

void MabbleIntro::draw(RenderWindow *window)
{
    for (int i = 0; i < numberOfIcons; i++)
    {
        switch (this->f)
        {
        case NEITHER:
            break;
        case FADE_IN:
            fade(FADE_IN);
            break;
        case FADE_OUT:
            fade(FADE_OUT);
            break;
        }
        icons[i].draw(window);
        window->draw(iconText[i]);
        switch (this->movement)
        {
        case NONE:
            break;
        case SINE:
            move_as_wave();
            break;
        case UP:
        case DOWN:
            move_straight();
            break;
        }
    }
    startButton->draw(window);
    window->draw(*startButtonText);
}

void MabbleIntro::set_opacity(byte_t alpha)
{
    for (int i = 0; i < numberOfIcons; i++)
    {
        Color c = icons[i].get_fill_color();
        icons[i].set_fill_color(Color(c.r, c.g, c.b, alpha));
        c = icons[i].get_outline_color();
        icons[i].set_outline_color(Color(c.r, c.g, c.b, alpha));
        c = iconText[i].getFillColor();
        iconText[i].setFillColor(Color(c.r, c.g, c.b, alpha));
    }
}

void MabbleIntro::fade(bool isFadingIn)
{
    if (!isFading)
    {
        this->seconds = seconds;
        this->f = isFadingIn ? FADE_IN : FADE_OUT;
        this->alpha = isFadingIn ? 0.0 : 255.0;
    }
}

void MabbleIntro::set_movement_to_wave()
{
    movement = SINE;
}

void MabbleIntro::set_movement_to_straight(Movement direction)
{
    movement = direction;
    for (int i = 0; i < numberOfIcons - 1; i++)
        canMoveStraight[i] = false;
}

void MabbleIntro::move_as_wave()
{
    for (int i = 0; i < numberOfIcons; i++)
    {
        icons[i].set_position(icons[i].get_xPos(), yPos + amplitude * sin(baseY[i]));
        set_text_position(&iconText[i], &icons[i]);
        baseY[i] += OFFSET;
        fmod(baseY[i], 2 * M_PI);
        cycle[i] = (cycle[i] + 1) % OFFSET_DIVISOR + 1;
    }
}

void MabbleIntro::move_straight()
{
    for (int i = numberOfIcons - 1; i > -1; i--)
    {
        if ((movement == UP ? cycle[i] == HIGHEST : cycle[i] == (int)LOWEST) && canMoveStraight[i + 1])
            canMoveStraight[i] = true;
        if (!canMoveStraight[i])
        {
            icons[i].set_position(icons[i].get_xPos(), yPos + amplitude * sin(baseY[i]));
            set_text_position(&iconText[i], &icons[i]);
            baseY[i] += OFFSET;
            fmod(baseY[i], 2 * M_PI);
            cycle[i]++;
            cycle[i] %= OFFSET_DIVISOR + 1;
        }
        else
        {
            if (movement == UP)
                icons[i].set_position(icons[i].get_xPos(), icons[i].get_yPos() - amplitude * abs(2 * OFFSET));
            else if (movement == DOWN)
                icons[i].set_position(icons[i].get_xPos(), icons[i].get_yPos() + amplitude * abs(2 * OFFSET));
            set_text_position(&iconText[i], &icons[i]);
        }
    }
}
void MabbleIntro::fade(Fade fade)
{
    if (fade == FADE_IN)
    {
        alpha += 0.01;
        set_opacity(static_cast<byte_t>(alpha));
        if (alpha >= 255.f)
        {
            set_opacity((byte_t)255);
            alpha = 255.0;
            isFading = false;
            this->f = NEITHER;
        }
    }
    else if (fade == FADE_OUT)
    {
        alpha -= 0.001;
        set_opacity(static_cast<byte_t>(alpha));
        if (alpha <= 0)
        {
            set_opacity((byte_t)0);
            alpha = 0.0;
            isFading = false;
            this->f = NEITHER;
        }
    }
}

void MabbleIntro::set_startButtonPosition(float xPos, float yPos)
{
    startButton->set_position(xPos, yPos);
}

void MabbleIntro::on_mouse_over(float mouseX, float mouseY, float screenX, float screenY)
{
    float x = mouseX - screenX + X_OFFSET;
    float y = mouseY - screenY + Y_OFFSET;
    if (x >= startButton->get_xPos() && x < startButton->get_xPos() + startButton->get_width() && y >= startButton->get_yPos() && y < startButton->get_yPos() + startButton->get_height())
    {
        change_startButton();
    }
    else
    {
        revert_startButton();
    }
}

void MabbleIntro::revert_startButton()
{
    startButton->set_size(158, 58);
    Vector2f pos = Vector2f(startButton->get_xPos(), startButton->get_yPos());
    startButton->set_fill_color(Color(131, 136, 164));
    startButton->set_outline_color(Color::Black);
    startButtonText->setFillColor(Color(255, 40, 104));
    startButtonText->setString("Ready?");
    set_text_position(startButtonText, startButton);
}

void MabbleIntro::change_startButton()
{
    Vector2f pos = Vector2f(startButton->get_xPos(), startButton->get_yPos());
    startButton->set_fill_color(Color(255, 94, 104));
    startButton->set_outline_color(Color::Black);
    startButtonText->setFillColor(Color(131, 136, 164));
    startButtonText->setString("Go!");
    set_text_position(startButtonText, startButton);
}

void MabbleIntro::gen_startButton(float xPos, float yPos)
{
    float width = 158;
    float height = 53;
    sbXPos = xPos - width / 2;
    sbYPos = yPos;
    startButton = new RoundedRectangle(xPos - width / 2, yPos, width, height, 5, 10);
    this->startButton->set_outline_color(Color::White);
    this->startButton->set_fill_color(Color::Black);
    startButton->set_thickness(2.f);
    startButtonText = new Text();
    startButtonText->setCharacterSize(30);
    startButtonText->setFillColor(Color::Red);
    startButtonText->setString("Ready?");
    startButtonText->setFont(font);
}

void MabbleIntro::set_text_position(Text *text, RoundedRectangle *rect)
{
    FloatRect lb = text->getLocalBounds();
    float xPos = rect->get_xPos(), yPos = rect->get_yPos();
    float width = rect->get_width(), height = rect->get_height();
    text->setOrigin(lb.left - xPos - (width - lb.width) / 2, lb.top - yPos - (height - lb.height) / 2);
}
void MabbleIntro::activate_logo(float mouseX, float mouseY, float screenX, float screenY)
{
    Vector2f pos = translate_to_screen(mouseX, mouseY, screenX, screenY);
    Vector2f buttonPos = Vector2f(startButton->get_xPos(), startButton->get_yPos());
    if (pos.x >= buttonPos.x && pos.x < buttonPos.x + startButton->get_width() && pos.y >= buttonPos.y && pos.y < buttonPos.y + startButton->get_height())
    {
        set_movement_to_straight(UP);
    }
}

Vector2f MabbleIntro::translate_to_screen(float mouseX, float mouseY, float screenX, float screenY)
{
    return Vector2f(mouseX - screenX + X_OFFSET, mouseY - screenY + Y_OFFSET);
}