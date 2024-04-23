export const templates = [
  {
    name: 'ATM 模块',
    code: `module ATM;
type
    Account = composed of
        balance: real
    end;
process Withdraw(amount: real | account1: Account)
e_msg: string | cash: real
ext wr account_file: set of Account
    rd account_file: set of Account
pre account1 inset account_file and account1.balance >= amount
post (exists[x: account_file] x = account1 and x.balance >= amount and cash = amount)
        and account_file = union(diff(~account_file, {account1}), {modify(account1, balance -> account1.balance - amount)})
        or not exists[x: account_file] x = account1 and x.balance >= amount and e_msg = "The amount is too big"
end_process;`,
  },
  {
    name: '复杂类型',
    code: `module A;
type
  A = int;
  B = real;
  C = composed of
    a: A;
    b: B;
  end;
  D = composed of
    a: A
    c: C;
  end;
  E = map int to string;
var
  e: D;

process Hello(input_f: A | input_g: B | str: string) output_h: C | output_i: D
ext rd files: E
pre (input_f + str) <> 0 and files(input_g) = "index" or (1+2) inset {1,2,3,4,5,6,7}
post output_i.c.b = output_h.b and input_f = output_h.a
end_process;`,
  },
];
