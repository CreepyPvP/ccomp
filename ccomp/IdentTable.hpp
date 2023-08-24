#pragma once

struct IdentTable;

struct IdentTableEntry {
    char* ident;
    int length;
    int value;

    IdentTableEntry* lNode;
    IdentTableEntry* rNode;

    int insertOrLookup(char* ident, int length, IdentTable* table);
};

struct IdentTable {
    IdentTableEntry* entryPool;
    int capacity;
    int nodeCount;

    void init();
    int insertOrLookup(char* ident, int length);
};
