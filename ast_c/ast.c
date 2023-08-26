#include <stdio.h>
#include <stdlib.h>

// Note: Inspired by Vladimir Keleshev's blog post: 
// https://keleshev.com/abstract-syntax-tree-an-example-in-c/

typedef enum
{
    AST_TYPE_main, 
    AST_TYPE_number, 
    AST_TYPE_add, 
    AST_TYPE_subtract, 
    AST_TYPE_multiply, 
    AST_TYPE_divide
} AST_Type;

typedef struct AST
{
    AST_Type tag;
    union
    {
        struct AST *body;
        int number;

        struct
        {
            struct AST *left;
            struct AST *right;
        } operation;
    } data;
} AST;

AST *ast_new(AST ast)
{
    AST *node = (AST *)malloc(sizeof(AST));
    if (node) *node = ast;
    return node;
}

int main(void)
{
    AST *root = ast_new((AST) {
        .tag = AST_TYPE_number, 
        .data.number = 10
    });

    printf("%d\n", root->data.number);
    return 0;
}
