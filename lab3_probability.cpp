#include <iostream>
#include <random>
#include <fstream>
#include<set>


using State = int;

class TypesState {
public:
    virtual bool contains(State s0) const = 0;
};

class DiscreteState : public TypesState {
private:
    State const s0;
public:
    DiscreteState(State s0) : s0(s0) {}
    bool contains(State s) const {
        return s == s0;
    }
};

class SegmentState : public TypesState {
private:
    State const begin_s0, end_s0;
public:
    SegmentState(State begin_s0, State end_s0) : begin_s0(begin_s0), end_s0(end_s0) {}
    bool contains(State s0) const {
        return begin_s0 <= s0 && end_s0 >= s0;
    }
};

class SetState : public TypesState {
private:
    std::set<int> const states;

public:
    SetState() : states() { }
    SetState(std::set<int> const& src) : states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

class UnionState : public TypesState {
private:
    TypesState& lha;
    TypesState& rha;
public:
    UnionState(TypesState& lha, TypesState& rha) : lha(lha), rha(rha) {}

    bool contains(State s0) const {
        return lha.contains(s0) || rha.contains(s0);
    }
};

class IntersectionState : public TypesState {
private:
    TypesState& lha;
    TypesState& rha;
public:
    IntersectionState(TypesState& lha, TypesState& rha) : lha(lha), rha(rha) {}

    bool contains(State s0) const {
        return lha.contains(s0) && rha.contains(s0);
    }
};

class ProbabilityTest {
private:
    State const E_min, E_max;

public:
    ProbabilityTest(State E_min, State E_max) : E_min(E_min), E_max(E_max) {}

    float test(TypesState const& system, unsigned test_count, unsigned seed) const {

        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt) {
            if (system.contains(dstr(reng))) ++good;

        }
        return static_cast<float>(good) / static_cast<float> (test_count);
    }
};

int main() {

    std::ofstream fout("output.txt");

    DiscreteState d(0);
    SegmentState s(0, 100);
    std::set<int> st = {1, 300, 275, -568, 1129, -5, 73};
    SetState tnt(st);
    ProbabilityTest pt(-1000, 1000);
    //UnionState a(s, d);
    //IntersectionState b(s, d);

    for (int i = 0; i < 1000; ++i) {
        fout << pt.test(tnt, i * 1000, 1) << '\n';
    }

    return 0;
}