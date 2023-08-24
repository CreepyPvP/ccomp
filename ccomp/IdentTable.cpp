#include "./IdentTable.hpp"
#include <assert.h>
#include <malloc.h>

#define internal static

internal int max(int a, int b) {
    if (a < b) return b;
    return a;
}

internal void createNode(char* ident, int length, IdentTable* table, IdentTableEntry* node) {
    assert(table->nodeCount < table->capacity);
    node->ident = ident;
    node->length = length;
    node->value = table->nodeCount;
    node->lNode = nullptr;
    node->rNode = nullptr;
    ++(table->nodeCount);
}

void IdentTable::init() {
    nodeCount = 0;
    entryPool = (IdentTableEntry*) malloc(capacity * sizeof(IdentTableEntry));
}

int IdentTable::insertOrLookup(char* ident, int length) {
    if (nodeCount > 0) {
        return entryPool->insertOrLookup(ident, length, this);
    } else {
        IdentTableEntry* node = entryPool;
        createNode(ident, length, this, node);
        return node->value;
    }
}

int IdentTableEntry::insertOrLookup(char* ident, int length, IdentTable* table) {
    for (int i = 0; i < max(length, this->length); ++i) {
        char selfValue = i < this-> length? this->ident[i] : 0;
        char identValue = i < length? ident[i] : 0;

        if (identValue == selfValue) {
            continue;
        }

        if (identValue <= selfValue) {
            if (lNode) {
                return lNode->insertOrLookup(ident, length, table);
            } else {
                lNode = table->entryPool + (table->nodeCount);
                createNode(ident, length, table, table->entryPool + (table->nodeCount));
                return lNode->value;
            }
        } else {
            if (rNode) {
                return rNode->insertOrLookup(ident, length, table);
            } else {
                rNode = table->entryPool + (table->nodeCount);
                createNode(ident, length, table, table->entryPool + (table->nodeCount));
                return rNode->value;
            }
        }
    }

    return this->value;
}
