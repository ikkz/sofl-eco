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
];
