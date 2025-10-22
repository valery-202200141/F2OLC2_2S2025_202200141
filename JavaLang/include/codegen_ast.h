#pragma once
#include "ast.h"
#include "codegen_arm64.h"

int codegen_arm64_generate(ast_node *root, const char *out_path);