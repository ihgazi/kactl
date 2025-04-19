/**
 * Author: Samrat Pal
 * Date: 2024-12-24
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: LazySegtree<ll> tr = new LazySegtree(sz);
 */
#pragma once

#include "../various/BumpAllocator.h"

enum QueryType { ADD, SET, NONE };
struct Query {
    QueryType type = NONE;
    ll val = 0;
};
template <typename T> class LazySegtree {
  private:
    const int sz;
    vector<T> tree;
    vector<Query> lazy;
    T combine(T a, T b) {
        return a+b;
    }
    void build(int v, int l, int r, const vector<T> &a) {
        if (l == r) {
            tree[v] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }
    void apply(int v, int len, const Query &x) {
        if (x.type == ADD) {
            if (lazy[v].type != SET) {
                lazy[v] = Query{ADD, lazy[v].val + x.val};
            } else {
                lazy[v] = Query{SET, lazy[v].val + x.val};
            }
            tree[v] += x.val * len;
        } else if (x.type == SET) {
            tree[v] = x.val * len;
            lazy[v] = x;
        }
    }
    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = Query();
    }
    void range_update(int v, int l, int r, int ql, int qr, const Query &x) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, r - l + 1, x);
        } else {
            push_down(v, l, r);
            int m = (l + r) / 2;
            range_update(2 * v, l, m, ql, qr, x);
            range_update(2 * v + 1, m + 1, r, ql, qr, x);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }
    T range_query(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) { return 0; }
        if (l >= ql && r <= qr) { return tree[v]; }
        push_down(v, l, r);
        int m = (l + r) / 2;
        return combine(range_query(2 * v, l, m, ql, qr), range_query(2 * v + 1, m + 1, r, ql, qr));
    }
  public:
    LazySegtree(const vector<T> &a) : sz(a.size()), tree(4 * sz), lazy(4 * sz) {
        build(1, 0, sz - 1, a);
    }
    LazySegtree(int n) : sz(n), tree(4 * sz), lazy(4 * sz) {
    }
    void range_update(int ql, int qr, const Query &x) {
        range_update(1, 0, sz - 1, ql, qr, x);
    }
    T range_query(int ql, int qr) { return range_query(1, 0, sz - 1, ql, qr); }
};
