#include <cstdio>

#include "PatternLanguage.h"

#include <unordered_map>

static uint64_t fakeId = 0x100;
static std::unordered_map<TreeNode, TreeNode> fakeTree;

static void *fakeNode(TreeNode parent)
{
    auto id = (TreeNode) fakeId++;
    fakeTree[id] = parent;
    return id;
}

int main(int argc, char **argv)
{
    auto source = R"(
struct Foo {
  u32 x;
  u8 y;
};

struct Cat {
  u16 meow;
};

struct Bar {
  Foo foo;
  u64 z;
};

struct Test {
  u8 a;
  u8 b;
  Cat c;
  Foo foo;
  u8 arr[10];
  Cat c2[2];
};

Test t @ 0x2;
)";

    auto logHandler = [](void *userdata, LogLevel level, const char *message)
    {
        puts(message);
    };
    auto compileError = [](void *userdata, const CompileError *error)
    {
        printf("[error:compile] %s\n", error->pretty);
    };
    auto evalError = [](void *userdata, const EvalError *error)
    {
        printf("[error:eval] %s\n", error->pretty);
    };
    auto dataSource = [](void *userdata, uint64_t address, void *buffer, size_t size)
    {
        auto buf = (uint8_t *) buffer;
        for (uint64_t i = 0; i < size; i++)
        {
            buf[i] = (address + i) & 0xFF;
        }
        return true;
    };
    auto visit = [](void *userdata, TreeNode parent, const VisitInfo *info) -> TreeNode
    {
        auto node = fakeNode(parent);
        printf("[%p->%p] %s %s |%s| (offset: 0x%llX, size: 0x%llX, line: %d)\n",
               parent,
               node,
               info->type_name,
               info->variable_name,
               info->value,
               info->offset,
               info->size,
               info->line
        );
        return node;
    };
    PatternRunArgs args = {
            .userdata = nullptr,
            .root = fakeNode(nullptr),
            .source = source,
            .filename = "<test>",
            .base = 0,
            .size = 0x10000,
            .log_handler = logHandler,
            .compile_error = compileError,
            .eval_error = evalError,
            .data_source = dataSource,
            .visit = visit,
    };
    printf("%s\n", source);
    PatternRun(&args);
    return 0;
}
