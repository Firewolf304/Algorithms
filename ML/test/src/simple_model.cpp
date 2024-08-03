//
// Created by firewolf on 13.07.24.
//
#include "simple_model.hpp"


simple_model ::~simple_model() {
    this->session->Close();
    delete this->session;
}

simple_model::simple_model(int xhidden_count, int yhidden_count) : inputs(inputs), outputs(outputs), xhidden_count(xhidden_count), yhidden_count(yhidden_count) {
    this->state = tensorflow::NewSession(tensorflow::SessionOptions(), &this->session);
    if(!this->state.ok()) {
        LOG(ERROR) << "Error creating session: " << state.message();
    }
}

tensorflow::NodeDef *simple_model::createSimpleNode(std::string name, std::string op) {
    tensorflow::NodeDef * node = this->graph.add_node();
    node->set_name(name);
    node->set_op(op);
    return node;
}


