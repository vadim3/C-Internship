#include <iostream>

/* Этот класс вам нужно реализовать */
struct PrintVisitor: Visitor {

    void visitNumber(Number const * number) {
        double x = number->evaluate();
        if(x < 0)
            std::cout << "(" << x << ")";
        else
            std::cout << x ;
    }

    void visitBinaryOperation(BinaryOperation const * bop) {
        bool is_prev = this->is; 
        char c = bop->get_op();
        bool is_cur = is_prev && (c == '-' || c == '+');
        if(is_cur)
            std::cout << "(";


        this->is = c=='*'||c=='/';   
        bop->get_left()->visit(this);

        std::cout << c;

        this->is = c=='*'||c =='/'; 
        bop->get_right()->visit(this);

        if(is_cur)
            std::cout << ")";
        this->is = is_prev;     
    }
private:
    bool is=false;
};
