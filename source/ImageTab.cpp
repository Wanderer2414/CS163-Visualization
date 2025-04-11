#include "../include/ImageTab.h"
#include "../include/General.h"

ImageTab::ImageTab() {
    gif_pointer = -1;
    clock.setDuration(4);
}
Vector2 ImageTab::getPosition() const {
    return Controller::getPosition();
}
void ImageTab::handle() {
    Move::handle();
    if (gif_pointer == -1 && gifs.size()) {
        gif_pointer++;
        gifs[gif_pointer]->setPosition(m_position.x, m_position.y);
        gifs[gif_pointer]->next();
    }
    if (gifs[gif_pointer]->getVertexDone() == 2) {
        gifs[gif_pointer]->setPosition(m_position.x+m_size.x, m_position.y);
        gifs[gif_pointer]->next();
        gif_pointer = (gif_pointer+1)%gifs.size();
    }
    if (gif_pointer>=0 && gif_pointer<gifs.size()) gifs[gif_pointer]->handle();
    if (gifs[(gif_pointer+1)%gifs.size()]->getVertexDone() == -1) 
        gifs[(gif_pointer+1)%gifs.size()]->handle();
    if (clock.get()) {
        gifs[gif_pointer]->next();
        gifs[(gif_pointer+1)%gifs.size()]->next();  
    }
    
}
void ImageTab::draw() {
    DrawRectangleRounded({m_position.x-5, m_position.y-5, m_size.x+10, m_size.y+10}, 0.1, 30, WHITE);
    BeginScissorMode(m_position.x, m_position.y, m_size.x, m_size.y);
    if (gif_pointer>=0 && gif_pointer<gifs.size()) gifs[gif_pointer]->draw();
    gifs[(gif_pointer+1)%gifs.size()]->draw();
    EndScissorMode();
}
void ImageTab::setSize(const float& x, const float& y) {
    Controller::setSize(x, y);
    for (int i = 0; i<gifs.size(); i++) gifs[i]->setSize(x, y);
}
void ImageTab::setPosition(const float& x, const float& y) {
    for (int i = 0; i<gifs.size(); i++) {
        Vector2 pos = gifs[i]->getPosition() - m_position + Vector2({x,y});
        gifs[i]->setVerticesPosition(pos.x, pos.y);
    }
    Controller::setPosition(x, y);
}
void ImageTab::push(const int& index, const string& str) {
    if (index==gifs.size()) {
        gifs.push_back(new GIF());
        gifs[index]->setPosition(m_position.x+m_size.x, m_position.y);
        gifs[index]->add_vertex({m_position.x+m_size.x, m_position.y});
        gifs[index]->add_vertex({m_position.x, m_position.y});
        gifs[index]->add_vertex({m_position.x-m_size.x, m_position.y});
        gifs[index]->setSize(m_size.x, m_size.y);
        gifs[index]->setDuration(0.7);
    }
    gifs[index]->push(str);
}
ImageTab::~ImageTab() {
    for (int i = 0; i<gifs.size(); i++) delete gifs[i];
}