#include "../include/Graph.h"
#include "../include/IncludePath.h"
#include "../include/General.h"

Graph::Graph(const int& index, FormSetting f_setting, const Vector2& window_size):
    Form(index, f_setting, window_size),
    notation_box(&form_setting),
    heap(&form_setting),
    track_graph_hover(&form_setting, &form_setting),
    graph_setting(&form_setting),
    setting_box(&form_setting),
    fixed_choice(&form_setting, 0, m_mode),
    drag_choice(&form_setting, 1, m_mode),
    collision_choice(&form_setting, 2, m_mode),
    weight_choice(&form_setting, 0, m_weight),
    unweight_choice(&form_setting, 1,m_weight),
    direct_choice(&form_setting, 0, m_type),
    undirect_choice(&form_setting, 1, m_type),

    dfs_choice(&form_setting, 0, search_type),
    bfs_choice(&form_setting, 1, search_type),

    search_graph_box(&form_setting),
    tools_box(&form_setting),
    dijikstra_button(&form_setting, &form_setting),
    prim_button(&form_setting, &form_setting),
    kruskal_button(&form_setting, &form_setting),

    algorithms_box(&form_setting),
    prim_box(&form_setting),
    kruskal_box(&form_setting),
    dijikstra_box(&form_setting),
    extract_box(&form_setting),

    extract_text_bx(&form_setting, &form_setting),
    dijikstra_textbox(&form_setting, &form_setting),
    prim_textbox(&form_setting, &form_setting),
    kruskal_textbox(&form_setting, &form_setting),
    pull_matrix_button(&form_setting, &form_setting),
    pull_input_textbox(&form_setting, &form_setting),

    vertex_label(&form_setting),
    edge_label(&form_setting),
    vertex_textbox(&form_setting, &form_setting),
    edge_textbox(&form_setting, &form_setting),

    color_box(&form_setting),

    color_pointer(-1)
{
    children.push_back(&track_graph_hover);
    children.push_back(&graph_setting); 

    setting_box.push_back(&fixed_choice);
    setting_box.push_back(&drag_choice);
    setting_box.push_back(&collision_choice);

    setting_box.push_back(&weight_choice);
    setting_box.push_back(&unweight_choice);

    setting_box.push_back(&direct_choice);
    setting_box.push_back(&undirect_choice);

    algorithms_box.push_back(0, &dijikstra_box);
    dijikstra_box.push_back(&dijikstra_textbox);
    dijikstra_box.push_back(&random_dijikstra_button);
    dijikstra_box.push_back(&dijikstra_button);

    algorithms_box.push_back(1, &prim_box);
    prim_box.push_back(&prim_textbox);
    prim_box.push_back(&random_prim_button);
    prim_box.push_back(&prim_button);

    algorithms_box.push_back(2, &kruskal_box);
    kruskal_box.push_back(&kruskal_textbox);
    kruskal_box.push_back(&random_kruskal_button);
    kruskal_box.push_back(&kruskal_button);

    tools_box.push_back(&match_tool);
    tools_box.push_back(&filled_tool);
    tools_box.push_back(&scissors_tool);

    extract_box.push_back(&extract_text_bx);
    extract_box.push_back(&pull_matrix_button);
    extract_box.push_back(&pull_input_textbox);

    search_graph_box.push_back(&dfs_choice);
    search_graph_box.push_back(&bfs_choice);

    //Setting box controller
    fixed_choice.setPosition(10, 5);
    fixed_choice.setSize(100, 30);
    fixed_choice.setText("Fixed");

    drag_choice.setPosition(10, 40);
    drag_choice.setSize(100, 30);
    drag_choice.setText("Drag");

    collision_choice.setPosition(10, 75);
    collision_choice.setSize(100, 30);
    collision_choice.setText("Collision");

    weight_choice.setPosition(170, 5);
    weight_choice.setSize(100, 30);
    weight_choice.setText("Weight");

    unweight_choice.setPosition(170, 40);
    unweight_choice.setSize(100, 30);
    unweight_choice.setText("Unweight");

    direct_choice.setPosition(170, 85);
    direct_choice.setSize(100, 30);
    direct_choice.setText("Direct");

    undirect_choice.setPosition(170, 120);
    undirect_choice.setSize(100, 30);
    undirect_choice.setText("Undirect");

    //Tool controller
    match_tool.setButtonStage(0, match_icon, match_filled_icon);
    match_tool.setPosition(5, 5);
    match_tool.setSize(40, 40);

    filled_tool.setButtonStage(0, fill_icon, fill_filled_icon);
    filled_tool.setPosition(50, 5);
    filled_tool.setSize(40, 40);

    scissors_tool.setButtonStage(0, scissor_icon, scissor_filled_icon);
    scissors_tool.setPosition(95, 5);
    scissors_tool.setSize(40, 40);
    //Algorithms
    dijikstra_textbox.setPosition(5, 5);
    dijikstra_textbox.setSize(100, 40);

    random_dijikstra_button.setPosition(110, 5);
    random_dijikstra_button.setSize(40, 40);
    random_dijikstra_button.setButtonStage(0, Rand, Rand);

    dijikstra_button.setPosition(155, 5);
    dijikstra_button.setSize(100, 40);
    dijikstra_button.setText("Start");

    prim_textbox.setPosition(5, 5);
    prim_textbox.setSize(100, 40);

    random_prim_button.setPosition(110, 5);
    random_prim_button.setSize(40, 40);
    random_prim_button.setButtonStage(0, Rand, Rand);

    prim_button.setPosition(155, 5);
    prim_button.setSize(100, 40);
    prim_button.setText("Start");

    kruskal_textbox.setPosition(5, 5);
    kruskal_textbox.setSize(100, 40);

    random_kruskal_button.setPosition(110, 5);
    random_kruskal_button.setSize(40, 40);
    random_kruskal_button.setButtonStage(0, Rand, Rand);

    kruskal_button.setPosition(155, 5);
    kruskal_button.setSize(100, 40);
    kruskal_button.setText("Start");

    algorithms_box.setText(0, "Dijikstra");
    algorithms_box.setText(1, "Prim");
    algorithms_box.setText(2, "Kruskal");

    dijikstra_box.setPosition(algorithms_box.getAutoSize().x + 15, 0);
    dijikstra_box.setSize(260, 50);

    prim_box.setPosition(algorithms_box.getAutoSize().x + 15, 45);
    prim_box.setSize(260, 50);

    kruskal_box.setPosition(algorithms_box.getAutoSize().x + 15, 90);
    kruskal_box.setSize(260, 50);
    //Extract controller
    extract_text_bx.setPosition(5, 5);
    extract_text_bx.setSize(290, 145);
    extract_text_bx.setAlignText(TextBox::Top | TextBox::Left);

    pull_matrix_button.setPosition(60, 155);
    pull_matrix_button.setSize(235, 40);
    pull_matrix_button.setText("Pull");

    pull_input_textbox.setPosition(5, 155);
    pull_input_textbox.setSize(50, 40);

    //Graph setting
    graph_setting.setPosition(-300, 100);
    graph_setting.setSize(300, 500);
    graph_setting.setText(0, "Settings");
    graph_setting.setText(1, "Tools");
    graph_setting.setText(2, "Algorithms");
    graph_setting.setText(3,"Extract");
    graph_setting.add_vertex({-300, 100});
    graph_setting.add_vertex({10, 100});
    graph_setting.setVisible(false);
    graph_setting.select(-1);

    setting_box.setSize(340, 170);
    setting_box.setPosition(graph_setting.getAutoSize().x + 15, 0);

    tools_box.setSize(200, 50);
    tools_box.setPosition(graph_setting.getAutoSize().x + 15, 45);

    algorithms_box.setPosition(graph_setting.getAutoSize().x + 15, 0);
    algorithms_box.setSize(300, 200);

    extract_box.setPosition(graph_setting.getAutoSize().x+15, 5);
    extract_box.setSize(300, 200);
    
    graph_setting.push_back(0, &setting_box);   
    graph_setting.push_back(1, &tools_box);
    graph_setting.push_back(2, &algorithms_box);
    graph_setting.push_back(3, &extract_box);

    track_graph_hover.setSize(10, graph_setting.getAutoSize().y);
    track_graph_hover.setPosition(0, 100);
    track_graph_hover.setText("");

    //Search box controller
    dfs_choice.setSize(100, 30);
    dfs_choice.setPosition(15, 5);
    dfs_choice.setText("Depth first search");

    bfs_choice.setSize(200, 30);
    bfs_choice.setPosition(15, 50);
    bfs_choice.setText("Breath first search");

    search_graph_box.setPosition(option_box.getAutoSize().x + 15, 30);
    search_graph_box.setSize(search_box.getSize().x, 100);
    option_box.push_back(3, &search_graph_box);

    //ReSetting console
    console_setting.font = LoadFont(font_link);
    console_setting.font_size = 20;
    console_setting.spacing = 2;
    console_setting.color = BLACK;
    console.text_setting = &console_setting;

    //Add random button to create box
    vertex_label.setText("V: ");
    vertex_label.setPosition(5, 35);
    vertex_label.setSize(30, 40);
    vertex_label.setAlignText(Label::Left | Label::Center);

    vertex_textbox.setPosition(40, 35);
    vertex_textbox.setSize(65, 40);
    vertex_textbox.setAlignText(TextBox::Left | TextBox::Center);

    random_vertex_button.setPosition(110, 40);
    random_vertex_button.setSize(30, 30);
    random_vertex_button.setButtonStage(0, Rand, Rand);

    edge_label.setText("E: ");
    edge_label.setPosition(160, 35);
    edge_label.setSize(30, 40);

    edge_textbox.setPosition(195, 35);
    edge_textbox.setSize(65, 40);
    edge_textbox.setAlignText(TextBox::Left | TextBox::Center);

    random_edge_button.setPosition(265, 40);
    random_edge_button.setSize(30, 30);
    random_edge_button.setButtonStage(0, Rand, Rand);
    
    create_textbox.setPosition(5, 80);
    create_button.setPosition(5, 190);

    create_box.push_back(&edge_label);
    create_box.push_back(&edge_textbox);
    create_box.push_back(&random_edge_button);
    create_box.push_back(&vertex_label);
    create_box.push_back(&vertex_textbox);
    create_box.push_back(&random_vertex_button);
    create_box.setSize(310, 240);
    create_box.reLocate(&create_textbox);
    create_box.reLocate(&create_button);

    color_box.setPosition(window_size.x - 500,100);
    color_box.setSize(120, 105);
    color_box.setVisible(false);

    heap.setPosition(15, 100);
    heap.setSize(100, 500);
    heap.setVisible(false);

    update_old_value_label.setText("Index: ");

    children.push_back(&color_box);
    children.push_back(&notation_box);

    srand(time(0));

    chosen = -1;
    m_mode = 2;
    m_weight = 1;
    m_type = 1;
    m_tool = -1;
    m_is_lock = false;
    search_type = 0;
};

void Graph::draw() {
    for (int i = 0; i<edges.size(); i++) {
        if (edges[i]) {
            if (m_type == 1) {
                int start = edges[i]->m_start->getIndex();
                int end = edges[i]->m_end->getIndex();
                if (matrix[end][start] != -1 && start<end) edges[i]->draw();
            } 
            else if (m_type == 0) edges[i]->draw();
        }
    }
    for (int i =0 ;i <vertices.size(); i++) 
        if (vertices[i]) vertices[i]->draw();
    for (int i = 0; i<DMargins.size(); i++) DMargins[i]->draw();
    heap.draw();
    Form::draw();

    if (m_tool==0) 
        DrawTexture(cursor_icon, GetMousePosition().x, GetMousePosition().y-cursor_icon.height, WHITE);
    else 
    if (m_tool==1) 
        DrawTexture(cursor_icon, GetMousePosition().x - cursor_icon.width, GetMousePosition().y, WHITE);
    else if (m_tool == 2) 
        DrawTexture(cursor_icon, GetMousePosition().x - cursor_icon.width/2, GetMousePosition().y-cursor_icon.height/2, WHITE);
}
void Graph::handle() {
    heap.handle();
    //Random create
    if (random_create.isPressed()) {
        int vertex = to_int(vertex_textbox.getText());
        int edge = to_int(edge_textbox.getText());
        if (vertex == 0) vertex_textbox.setText(RandomVertex());
        vertex = to_int(vertex_textbox.getText());
        if (edge < vertex - 1 || edge > vertex*(vertex-1)/2) 
            edge_textbox.setText(RandomEdge());
        create_textbox.setText(RandomCreate());
    }
    if (random_edge_button.isPressed()) {
        edge_textbox.setText(RandomEdge());
    }
    if (random_vertex_button.isPressed()) {
        vertex_textbox.setText(RandomVertex());
    }
    Form::handle();
    for (int i = 0; i<edges.size(); i++) {
        if (edges[i]) {
            if (m_type == 1) {
                int start = edges[i]->m_start->getIndex();
                int end = edges[i]->m_end->getIndex();
                if (matrix[start][end]==-1 || matrix[end][start] == -1) continue;
            } 
            edges[i]->handle();
            edges[i]->setMode(m_weight == 0);

            //Vertex color change
            if (!m_is_lock && edges[i]->m_start->IsColorChange() && (edges[i]->m_start->getColor() != edges[i]->start_color)) {
                int start = edges[i]->m_start->getIndex();
                int end = edges[i]->m_end->getIndex();
                if (m_type == 1) {
                    if (start<end) {
                        edges[i]->setDuration(getSpeed());
                        edges[i]->start(false, false);
                    }
                    else {
                        edges[i]->setDuration(getSpeed());
                        edges[matrix[end][start]]->start(true, false);
                    }
                }
                else {
                    edges[i]->setDuration(getSpeed());
                    edges[i]->start(false, false);
                }
            }
            //Check press delete
            if (edges[i]->isPressed()) {
                if (m_tool == 2) {
                    int start = edges[i]->m_start->getIndex(), end = edges[i]->m_end->getIndex();
                    cout << i << endl;
                    InsertNextMainCommand({remove_edge,1.0f*i, 1.0f*start, 1.f*end, 1.0f*edges[i]->getWeight(), 1});
                }
            }
            //Check edge color change 
            if (edges[i]->IsColorChange() && !m_is_lock) {
                if (!edges[i]->IsReverse()) {
                    float angular = arctan(edges[i]->m_start->getCenter() - edges[i]->m_end->getCenter());
                    edges[i]->m_end->setDuration(getSpeed());
                    edges[i]->m_end->start(angular, edges[i]->start_color, edges[i]->m_end->getColor());
                } else {
                    float angular = arctan(edges[i]->m_end->getCenter() - edges[i]->m_start->getCenter());
                    edges[i]->m_start->setDuration(getSpeed());
                    edges[i]->m_start->start(angular, edges[i]->end_color, edges[i]->m_start->getColor());
                }
            }
        }
    }
    bool isFocus = false;
    notation_box.hide();
    for (int i = 0; i<vertices.size(); i++) {
        if (vertices[i]) {
            vertices[i]->handle();
            vertices[i]->setFixed(m_mode == 0);
            vertices[i]->setDragable(m_mode == 1);

            //Match vertex
            if (vertices[i]->isFocused()) {
                isFocus = true;
                if (m_tool == 1 && i!=chosen) {
                    for (int i = 0; i<edges.size(); i++)
                        if (edges[i]) edges[i]->complete();
                    for (int i = 0; i<vertices.size(); i++)
                        if (vertices[i]) vertices[i]->complete();
                    vertices[i]->setDuration(getSpeed());
                    vertices[i]->start(0, color_box.getColor(), vertices[i]->getColor());
                }
                if (chosen == -1) chosen = i;
                else if (chosen != i) {
                    if (m_tool == 0) {
                        console.InsertNextMainCommand("Match " + to_string(vertices[chosen]->getValue()) + " to " + to_string(vertices[i]->getValue()));
                        InsertNextMainCommand({match_code, 1.0f*edges.size(), 1.0f*chosen, 1.0f*i, 1, 0.1});
                        edges.push_back(0);
                        if (m_type == 1) {
                            console.InsertNextMainCommand("Match " + to_string(vertices[i]->getValue()) + " to " + to_string(vertices[chosen]->getValue()));
                            InsertNextMainCommand({match_code, 1.0f*edges.size(), 1.0f*i, 1.0f*chosen, 1, 0.1});
                            edges.push_back(0);
                        }
                    }
                    chosen = i;
                }
                if (IsKeyPressed(KEY_DELETE)) {
                    remove(i);
                    chosen = -1;
                } else if (IsKeyPressed(KEY_F2)) {
                    main_box_show();
                    option_box.select(2);
                    update_textbox_choice.setText(to_string(vertices[i]->getIndex()));
                    update_textbox_value.setFocus(true);
                }
                if (m_tool == -1) {
                    notation_box.vertex = vertices[i];
                    notation_box.setPosition(vertices[i]->getPosition().x + vertices[i]->getSize().x/2, vertices[i]->getPosition().y-vertices[i]->getSize().y/2-notation_box.getSize().y);
                    notation_box.show();
                }
            }
            //Check out window
            if (m_mode != 0) {
                Vector2 pos = vertices[i]->getCenter();
                float radius = vertices[i]->getRadius();
                Vector2 velocity = {0, 0}, acceleration = {0, 0};
                if (pos.x-radius<m_workspace.x)                             {
                    acceleration.x = -vertices[i]->getVelocity().x*1.8;
                    vertices[i]->setPosition(m_workspace.x + radius, pos.y);
                }
                else if (pos.x+radius>m_workspace.x + m_workspace.width)    {
                    acceleration.x = - vertices[i]->getVelocity().x*1.8;
                    vertices[i]->setPosition(m_workspace.x + m_workspace.width - radius, pos.y);
                }
                if (pos.y - radius<m_workspace.y)                           {
                    acceleration.y = -vertices[i]->getVelocity().y*1.8;
                    vertices[i]->setPosition(pos.x, m_workspace.y + radius);
                }
                else if (pos.y+radius > m_workspace.y + m_workspace.height) {
                    acceleration.y = -vertices[i]->getVelocity().y*1.8;
                    vertices[i]->setPosition(pos.x, m_workspace.y + m_workspace.height - radius);
                }
                vertices[i]->add_acceleration(acceleration);
                //Check collision
                for (int j = i+1; j<vertices.size(); j++) {
                    if (vertices[j]) {
                        if (abs(vertices[i]->getCenter()-vertices[j]->getCenter()) < vertices[i]->getRadius() + vertices[j]->getRadius()) {
                            Vector2 delta = vertices[j]->getCenter() - vertices[i]->getCenter();
                            delta = delta/abs(delta)*(vertices[i]->getRadius() + vertices[j]->getRadius() - abs(delta));
                            if (m_mode == 2) {
                                Vector2 velocityA = vertices[i]->getVelocity();
                                Vector2 velocityB = vertices[j]->getVelocity();
                                vertices[i]->setVelocity(velocityB - delta/10);
                                vertices[j]->setVelocity(velocityA + delta/10);
                            } else {
                                Vector2 posA = vertices[i]->getPosition() - delta*1.1;
                                Vector2 posB = vertices[j]->getPosition() + delta*1.1;
                                vertices[i]->setPosition(posA.x, posA.y);
                                vertices[j]->setPosition(posB.x, posB.y);
                            }
                        }
                    }
                }
            }
            //Check hover 
            if (vertices[i]->isHovered() && m_tool == -1) {
                notation_box.vertex = vertices[i];
                notation_box.setPosition(GetMousePosition().x,GetMousePosition().y-notation_box.getSize().y);
                notation_box.show();
            }
        }
    }
    //Open Color pointer
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && m_tool == 1) {
        color_box.setVisible(true);
        color_box.setPosition(GetMousePosition().x, GetMousePosition().y);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_tool == 1 && !color_box.isHovered()) {
        color_box.setVisible(false);
    }
    //Change type
    if (direct_choice.isChanged() && direct_choice.isPressed()) {
        for (int i = 0; i<edges.size(); i++) {
            if (edges[i]) {
                int start = edges[i]->m_start->getIndex();
                int end = edges[i]->m_end->getIndex();
                if (start>end && matrix[end][start] != -1) edges[i]->setColor(edges[matrix[end][start]]->start_color);
                edges[i]->setType(true);
            }
        }
    } else if (undirect_choice.isChanged() && undirect_choice.isPressed()) {
        for (int i = 0; i<edges.size(); i++) {
            if (edges[i]) {
                edges[i]->setType(false);
                if (edges[i]->m_start->getColor() != edges[i]->m_end->getColor()) {
                    edges[i]->setDuration(getSpeed());
                    edges[i]->start(false, false);
                }
            }
        }
    }
    if (!isFocus) chosen = -1;
    //Graph box show
    if (track_graph_hover.isHovered()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = track_graph_hover.getPosition();
            pos.y += GetMouseDelta().y;
            track_graph_hover.setPosition(pos.x, pos.y);
            pos = graph_setting.getPosition();
            pos.y += GetMouseDelta().y;
            graph_setting.setPosition(pos.x, pos.y);
        }
        if (graph_setting.getVertexDone() == 0) {
            graph_setting.setVisible(true);
            graph_setting.next();
        }
    }
    else if (!graph_setting.isHovered()) {
        if (graph_setting.getVertexDone() == 0)
            graph_setting.setVisible(false);
        else if (graph_setting.getVertexDone() == 1) {
            graph_setting.next();
            graph_setting.select(-1);
        }
    }
    //Insert edge/ Match tool press
    if (match_tool.isPressed()) {
        if (m_tool != 0) {
            if (m_tool!=-1) UnloadTexture(cursor_icon);
            else HideCursor();
            m_tool = 0;
            cursor_icon = LoadTexture(match_cursor_icon);
            cursor_icon.width = cursor_icon.height = 30;
        }
        else {
            ShowCursor();
            UnloadTexture(cursor_icon);
            m_tool = -1;
        }
    }
    if (filled_tool.isPressed()) {
        if (m_tool != 1) {
            if (m_tool!=-1) UnloadTexture(cursor_icon);
            else HideCursor();
            m_tool = 1;
            cursor_icon = LoadTexture(fill_cursor_icon);
            cursor_icon.width = cursor_icon.height = 30;
        }
        else {
            ShowCursor();
            UnloadTexture(cursor_icon);
            m_tool = -1;
        }
    }
    if (scissors_tool.isPressed()) {
        if (m_tool != 2) {
            if (m_tool!=-1) UnloadTexture(cursor_icon);
            else HideCursor();
            m_tool = 2;
            cursor_icon = LoadTexture(scissor_cursor_icon);
            cursor_icon.width = cursor_icon.height = 30;
        }
        else {
            ShowCursor();
            UnloadTexture(cursor_icon);
            m_tool = -1;
        }
    }
    //Update check
    //Matrix pull
    if (pull_matrix_button.isPressed()) {
        pull_matrix(to_int(pull_input_textbox.getText()));
    }
    //Alogoritm check 
    if (prim_button.isPressed()) {
        prim(prim_textbox.getText());
    }
    if (kruskal_button.isPressed()) {
        kruskal(kruskal_textbox.getText());
    }
    if (dijikstra_button.isPressed()) {
        dijikstra(dijikstra_textbox.getText());
    }
}

void Graph::search(const string& val) {
    float i = to_int(val);
    if (i<vertices.size()) {
        int value = vertices[i]->getValue();
        if (search_type == 0)
            console.InsertNextMainCommand("Search " + to_string(value) + " with DFS");
        else console.InsertNextMainCommand("Search " + to_string(value) + " with BFS");
        InsertNextMainCommand({search_code, 1.0f*search_type, i, 0});
    }
}

void Graph::add(const vector<std::string>& str) {
    if (str.size()>1) {
        int n = to_int(str[0]);
        true_color.resize(true_color.size() + n, colors[(color_pointer+1)%6]);
        for (int i = 0; i<n; i++) {
            vertices.push_back(new Vertex(&form_setting, vertices.size()));
            float x = 1.0f*rand()/RAND_MAX*m_window_size.x;
            float y = 1.0f*rand()/RAND_MAX*m_window_size.y;
            vertices.back()->setPosition(x, y);
            vertices.back()->setSize(50, 50);;
            vertices.back()->setValue(matrix.size()+i);
        }
        int delta = n+matrix.size();

        matrix.resize(delta, {});
        for (int i = 0; i<matrix.size(); i++) matrix[i].resize(delta, -1);

        delta -= n;
        for (int i = delta; i<n+delta; i++) {
            for (int j = delta; j<n+delta; j++) {
                int weight = to_int(str[(i-delta)*n+(j-delta)+1]);
                if (weight && i != j) {
                    matrix[i][j] = edges.size();
                    edges.push_back(new Edge(vertices[i], vertices[j], &form_setting));
                    edges.back()->setWeight(weight);
                    if (i<j) edges.back()->setType(m_type == 0);
                }
            }
        }
        setSubGraphColor(delta, colors[(++color_pointer)%6]);
        for (int i = 0; i<edges.size(); i++) 
            if (edges[i]) edges[i]->start(false);
    } else {
        InsertNextMainCommand({add_code, 1.0f*to_int(str[0]),1});
    }
}

void Graph::remove(const std::string& str) {
    int i = to_int(str);
    if (i<vertices.size()) {
        remove(i);
    }
}