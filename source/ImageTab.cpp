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
        gifs[gif_pointer]->moveNext();
    }
    if (gifs[gif_pointer]->getVertexDone() == 2) {
        gifs[gif_pointer]->setPosition(m_position.x+m_size.x, m_position.y);
        gifs[gif_pointer]->moveNext();
        gif_pointer = (gif_pointer+1)%gifs.size();
    }
    if (gif_pointer>=0 && gif_pointer<gifs.size()) gifs[gif_pointer]->handle();
    if (gifs[(gif_pointer+1)%gifs.size()]->getVertexDone() == -1) 
        gifs[(gif_pointer+1)%gifs.size()]->handle();
    if (clock.get()) {
        gifs[gif_pointer]->moveNext();
        gifs[(gif_pointer+1)%gifs.size()]->moveNext();  
    }
    
}
void ImageTab::draw() {
    if (m_position.x + m_size.x < 0) return;
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
void ImageTab::push(GIF* gif) {
    gifs.push_back(gif);
    gif->clearVertices();
    gif->setPosition(m_position.x+m_size.x, m_position.y);
    gif->add_vertex({m_position.x+m_size.x, m_position.y});
    gif->add_vertex({m_position.x, m_position.y});
    gif->add_vertex({m_position.x-m_size.x, m_position.y});
    gif->setSize(m_size.x, m_size.y);
    gif->setDuration(0.7);
}
void ImageTab::clearGifs() {
    gifs.clear();
    gif_pointer = -1;
}
ImageTab::~ImageTab() {
    clearGifs();
}