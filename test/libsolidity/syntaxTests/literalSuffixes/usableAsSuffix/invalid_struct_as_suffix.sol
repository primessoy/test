struct S {
    uint x;
}

contract C {
    uint a = 1000 S;
}
// ----
// TypeError 4438: (52-58): The literal suffix must be either a subdenomination or a file-level suffix function.
