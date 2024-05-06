export const templates = [
  {
    name: 'Showcase1',
    code: `module Command;

process init()
pre true
post true
end_process;

process Receive_Command(balance:real | w_draw:real) sel: bool
pre true
post bound(balance)  and sel = true or bound(w_draw)  and sel = false
end_process;`,
  },
  {
    name: 'Showcase2',
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
    name: 'Showcase3',
    code: `module ATM;
type
    Account = composed of
        balance: real;
        account_no: nat;
        password: nat;
    end;

process Check_Password(card_id: nat| sel: bool| pass: nat)
                                      account1: Account | 
                                      pr_meg: string | 
                                      account2: Account
ext
  rd account_file: set of Account
pre true
post sel = false and 
               (exists[x: account_file] x.account_no = card_id and x.password = pass and account1 = x) or 
               sel = true and
               (exists[x: account_file] x.account_no = card_id and x.password= pass and account2 =x) or 
               not (exists[x: account_file] x.account_no = card_id and x.password = pass) and pr_meg = "Reenter 
               your password or insert thecorrect card"                         
end_process;`,
  },
];
