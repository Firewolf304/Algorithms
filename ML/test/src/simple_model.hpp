//
// Created by firewolf on 13.07.24.
//

#pragma once

#include <tensorflow/cc/client/client_session.h>
#include <tensorflow/core/public/session.h>
#include <tensorflow/cc/ops/standard_ops.h>
#include <tensorflow/core/framework/tensor.h>
#include <tensorflow/core/framework/graph.pb.h>
#include <tensorflow/core/framework/node_def.pb.h>
#include <tensorflow/core/framework/op.h>
#include <generator>


class simple_model {
private:
    tensorflow::GraphDef graph;
    tensorflow::Session* session;
    tensorflow::Status state;
    int inputs = 3, outputs = 1, xhidden_count = 1, yhidden_count = 1;
public:
    explicit simple_model(int xhidden_count = 2, int yhidden_count = 2);
    ~simple_model();
    tensorflow::NodeDef *  createSimpleNode(std::string name = "", std::string op = "");

    enum file_types : int {
        pb = 0,
        pbtxt = 1
    };

    template<bool visualise = false, file_types type = pbtxt>
    void create_model() {

        // inputs
        /*auto gen = [&]() -> std::generator<tensorflow::NodeDef*> {
            for(int i = 0; i < this->inputs; i++) {
                co_yield createSimpleNode("input_" + std::to_string(i), "Placeholder");
            }
        };
        auto hidden = createSimpleNode("concat", "ConcatV2");
        for(auto node : gen()) {
            (*node->mutable_attr())["dtype"].set_type(tensorflow::DT_FLOAT);
            (*node->mutable_attr())["shape"].mutable_shape()->add_dim()->set_size(-1);

            hidden->add_input(node->name());
        }*/

        // inputs
        // a
        tensorflow::NodeDef* a_node = createSimpleNode("input_a", "Placeholder");
        (*a_node->mutable_attr())["dtype"].set_type(tensorflow::DT_FLOAT);
        (*a_node->mutable_attr())["shape"].mutable_shape()->add_dim()->set_size(1);

        // op
        tensorflow::NodeDef* op_node = createSimpleNode("input_op", "Placeholder");
        (*op_node->mutable_attr())["dtype"].set_type(tensorflow::DT_STRING);
        (*op_node->mutable_attr())["shape"].mutable_shape()->add_dim()->set_size(1);

        // b
        tensorflow::NodeDef* b_node = createSimpleNode("input_b", "Placeholder");
        (*b_node->mutable_attr())["dtype"].set_type(tensorflow::DT_FLOAT);
        (*b_node->mutable_attr())["shape"].mutable_shape()->add_dim()->set_size(1);

        /**
         * sum - '+'
         * div - '/'
         * mul - '*'
         * sub - '-'
         */

        // sum
        tensorflow::NodeDef* sum_node = createSimpleNode("sum", "Add");
        sum_node->add_input("input_a");
        sum_node->add_input("input_b");
        (*sum_node->mutable_attr())["T"].set_type(tensorflow::DT_FLOAT);

        tensorflow::NodeDef* sum_const = createSimpleNode("sum_const", "Const");
        (*sum_const->mutable_attr())["dtype"].set_type(tensorflow::DT_STRING);
        (*sum_const->mutable_attr())["value"].mutable_tensor()->set_dtype(tensorflow::DT_STRING);
        (*sum_const->mutable_attr())["value"].mutable_tensor()->add_string_val("+"); // +

        tensorflow::NodeDef* sum_equal = createSimpleNode("sum_equal", "Equal");
        sum_equal->add_input("input_op");
        sum_equal->add_input("sum_const");
        (*sum_equal->mutable_attr())["T"].set_type(tensorflow::DT_STRING);


        // div
        tensorflow::NodeDef* div_node = createSimpleNode("div", "Div");
        div_node->add_input("input_a");
        div_node->add_input("input_b");
        (*div_node->mutable_attr())["T"].set_type(tensorflow::DT_FLOAT);

        tensorflow::NodeDef* div_const = createSimpleNode("div_const", "Const");
        (*div_const->mutable_attr())["dtype"].set_type(tensorflow::DT_STRING);
        (*div_const->mutable_attr())["value"].mutable_tensor()->set_dtype(tensorflow::DT_STRING);
        (*div_const->mutable_attr())["value"].mutable_tensor()->add_string_val("/"); // /

        tensorflow::NodeDef* div_equal = createSimpleNode("div_equal", "Equal");
        div_equal->add_input("input_op");
        div_equal->add_input("div_const");
        (*div_equal->mutable_attr())["T"].set_type(tensorflow::DT_STRING);

        // mul
        tensorflow::NodeDef* mul_node = createSimpleNode("mul", "Mul");
        mul_node->add_input("input_a");
        mul_node->add_input("input_b");
        (*mul_node->mutable_attr())["T"].set_type(tensorflow::DT_FLOAT);

        tensorflow::NodeDef* mul_const = createSimpleNode("mul_const", "Const");
        (*mul_const->mutable_attr())["dtype"].set_type(tensorflow::DT_STRING);
        (*mul_const->mutable_attr())["value"].mutable_tensor()->set_dtype(tensorflow::DT_STRING);
        (*mul_const->mutable_attr())["value"].mutable_tensor()->add_string_val("*"); // *

        tensorflow::NodeDef* mul_equal = createSimpleNode("mul_equal", "Equal");
        mul_equal->add_input("input_op");
        mul_equal->add_input("mul_const");
        (*mul_equal->mutable_attr())["T"].set_type(tensorflow::DT_STRING);

        // sub
        tensorflow::NodeDef* sub_node = createSimpleNode("sub", "Sub");
        sub_node->add_input("input_a");
        sub_node->add_input("input_b");
        (*sub_node->mutable_attr())["T"].set_type(tensorflow::DT_FLOAT);

        tensorflow::NodeDef* sub_const = createSimpleNode("sub_const", "Const");
        (*sub_const->mutable_attr())["dtype"].set_type(tensorflow::DT_STRING);
        (*sub_const->mutable_attr())["value"].mutable_tensor()->set_dtype(tensorflow::DT_STRING);
        (*sub_const->mutable_attr())["value"].mutable_tensor()->add_string_val("-"); // -

        tensorflow::NodeDef* sub_equal = createSimpleNode("sub_equal", "Equal");
        sub_equal->add_input("input_op");
        sub_equal->add_input("sub_const");
        (*sub_equal->mutable_attr())["T"].set_type(tensorflow::DT_STRING);

        tensorflow::NodeDef* switch_op = createSimpleNode("switch_op", "Switch");
        (*switch_op->mutable_attr())["shape"].mutable_shape()->add_dim()->set_size(-1);
        switch_op->add_input("sum_const");
        switch_op->add_input("sum_equal");

        switch_op->add_input("div_const");
        switch_op->add_input("div_equal");

        switch_op->add_input("mul_const");
        switch_op->add_input("mul_equal");

        switch_op->add_input("sub_const");
        switch_op->add_input("sub_equal");
        (*switch_op->mutable_attr())["T"].set_type(tensorflow::DT_STRING);

        tensorflow::NodeDef* switch_res = createSimpleNode("switch_res", "Switch");
        switch_res->add_input("switch_op");
        switch_res->add_input("sum");

        switch_res->add_input("switch_op");
        switch_res->add_input("div");

        switch_res->add_input("switch_op");
        switch_res->add_input("mul");

        switch_res->add_input("switch_op");
        switch_res->add_input("sub");
        (*switch_res->mutable_attr())["T"].set_type(tensorflow::DT_FLOAT);

        state = this->session->Create(this->graph);
        if (!state.ok()) {
            LOG(ERROR) << "Error creating graph in session: " << state.message();
        }
        if(visualise) {
            switch(type) {
                case pb : {
                    state = tensorflow::WriteBinaryProto(tensorflow::Env::Default(), "model.pb", this->graph);
                }break;
                case pbtxt: {
                    state = tensorflow::WriteTextProto(tensorflow::Env::Default(), "model.pbtxt", this->graph);
                }break;
            }
            if(!state.ok()) {
                LOG(ERROR) << "Error saving graph in session: " << state.message();
            }
        }
    }
};

auto simple = []() {
    using namespace tensorflow;
    using namespace tensorflow::ops;
    Scope root = Scope::NewRootScope();
    // Matrix A = [3 2; -1 0]
    auto A = Const(root, {{3.f, 2.f}, {-1.f, 0.f}});
    // Vector b = [3 5]
    auto b = Const(root, {{3.f, 5.f}});
    // v = Ab^T
    auto v = MatMul(root.WithOpName("v"), A, b, MatMul::TransposeB(true));
    std::vector<Tensor> outputs;
    ClientSession session(root);

    TF_CHECK_OK(session.Run({v}, &outputs));

    LOG(INFO) << outputs[0].matrix<float>();
};




