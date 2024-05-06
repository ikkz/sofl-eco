export const symbols = `module BuiltinSymbols;

function
    abs<T>(T): T;
    bound<T>(T): bool;
    floor<T>: T;

    union<T>(T, T): T;
    inter<T>(T, T): T;
    diff<T>(T, T): T;
    len<T>(T): int;
    power<T1, T2>(T1, T2): T1;
`;
