The module code deliverables come in three parts:

  Deliverable                  | Due         | Weight | Notes
-------------------------------|-------------|--------|------------------------------------
[1-lexer.md](1-lexer.md)       | Tue 7th Feb | 10%    | A C lexer that produces JSON output 
[2-parser.md](2-lexer.md)      | Tue 7th Mar | 10%    | A (restricted) C parser that produces XML output
[3-compiler.md](3-compiler.md) | Tue 7th Feb | 50%    | The final C compiler

You will all get a bare private repository. It is up to you
if you want to clone the master specification, or to start from
scratch. Both approaches just require the git operations already used
in lab 1, and possibly looking at the documentation for the commands
you have already used. Remember that you can always do `git ${CMD} --help`
for any CMD such as `pull`, `push`, `commit`, `remote`.

Starting from scratch
---------------------

1 - Create a local git repository using `git init` in a directory of your choice.

2 - Commit files to your local repository (as you would normally commit)

3 - Add the URL of your private repository as the remote `origin` (similar
    to manually adding the `spec` remote in the lab).

4 - You should now be able to push and pull commits to origin, which is
    your private repo.
    
Cloning the spec
----------------

1 - Clone the master specification from the public URL. This will produce
    a directory called `langproc-2016-cw` by default.
    
2 - Rename it to something more meaningful, e.g. `langproc-2016-cw-${LOGIN}`.

3 - Use `git remote` to rename `origin` (which points at the public spec) to
    `spec`.
    
4 - Use `git remote` to add a new remote called `origin` pointing at
    your private repository.

5 - You should then be able to push and pull to `origin`, and pull from `spec`,
    as in the lab.

Submissions
-----------

Submission will be via github (code) + blackboard (commit hash),
as in the lab.
