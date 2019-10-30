# Git, C, CMake and State Machine Tutorial

## Getting Started

To do this tutorial you must fork this by clicking the fork button in the GitHub web interface. The instructions will always appear in the root folder of the repo and can be viewed in the web interface.

## Welcome

Hello and welcome to this Git tutorial. I am to help you get some savvy Git skills whilst also using the C compilation process and a C project as a means to provide a reasoning behind the power and necessity of Git. The C projects will also demonstrate how a state machine works and a basic way of implementing one.

Please note that if you're reading these instruction whilst doing the tutorial they may dissapear if you change branch or do some git trickery that causes them to move/change. As such, while you get to grips with Git I would reccomend moving these README.md files, as they become available, somewhere outside of the current Git repo while you complete the challenge.

## Git

So what is Git?

I hope you all already know the answer to this. Git is a version control software that is now more or less the gold standard in code version control used around the world. As such, knowing Git is a very important skill in today's workplace for anyone that has anything to do with the development of code, regardless of the code type. It can be useful not just code projects but for the version control of any sort of project based around non-binary files, such as PCB designs.

So without writing a big blurb on Git, I say we just get into it and learn by doing.

## What is Forking?

So you will of now forked my repo from GitHub. What this means is that you have more or less copied (not cloned) my repo. It is a complete copy, including the Git histroy, Git objects etc. The key point is that it now belongs to you and you can do as you wish with it, without disturbing my original repo. It is a handy feature that is implemented by the Git server systems (such as GitLab and GitHub), it is not intrinsically a part of Git. It allows for developers to essentially snapshot someone's project, modify it and then, if they want, they can send the changes back to the original developer who can decide if they want to merge their changes into the original code. Forking is popular in the open source community where people are not always directly included in someone's project.

Throughout this tutorial we will do two things, we will set up a new repository for you to use throughout the semester to manage your code and we will undertake some little challenges in this repository to help further your Git and C abilities.

## Basics

Now the very basics of Git. Git works using repositories (previously mentioned repos). Repos are essentially a mini filesystem (locally seen as a folder) in which all changes, that happen within that folder, are (or can be) tracked. Git monitors changes to files and stores snapshots of the files at specified points. By snapshotting the file system, Git gives each point point in the repo's history a unique value. Enabling a developer to revert changes, go back and look at previous, or parallel, version as well as lots of other cool stuff we will cover a bit more later.

Without going into it too much now, we know that a Git repo will give us a folder, whose content will be tracked. So now let's set up the repo that you will use throughout semester.

For anyone doing this that is not one of my students you will have to just ignore the specifics aimed at my students.

You can either use the LRZ GitLab or a **private** GitHub repo for this, the functionality is identical. Do not use a public GitHub as other students will be able to view your code and you might be involved in some nasty business if duplicate code is found in another student's project.

So now you will need to create a new project. This will require you to do the following:

1. Create a new project/repository in the web GUI
2. Either follow the given instructions to clone the new repository or copy the clone link so you can clone the repository to your machine which I will explain now.

  There are two types of links always available, one via SSH and the other via HTTPS. SSH allows you to upload your public SSH key to the server and use it to authenticate yourself when interacting with the server, meaning you do not have to constantly enter your username and password when interacting with the server. In contrast HTTPS requires you to enter your username and password in the terminal every time you interact with the server when authentication is required.

  I recommend uploading a SSH key and using the SSH link. Google how to do this, its not hard.

  Then to clone the repository you simply have to run the `git clone` command. Looking at the manual page for the clone command (`man git clone`) we can see that the command takes the form of `git clone <options> <repository> <directory>`. For us we will just use the basic command to clone our newly created repository into a folder called "ESPL_code". From the folder where you would like to have your `ESPL_code` folder stored run

  ``` bash
  git clone <SSH or HTTPS URL> ESPL_code
  ```

  Now we will have the Git repo on our local machines. Next we will look into the basics of creating and storing code in our repository. Please note that after the basics of the "ESPL_code" repository are set up we will do the rest of this tutorial in the tutorial repository, I am just wanting to make sure you have a Git repo set up and ready for the rest of semester so that you USE IT!

# How Git Tracks Your Changes

Git works slightly differently to other version control software in that is uses a staging area to which a user adds files that he/she wishes to be tracked (changes recorded). As such Git does not automatically track all changes in a repository. It is up to the user to make sure that the files that they are interested in are added to the staging area, there are ways to wildcard add things but this can lead to very messy and unprofessional repos.

As such the workflow follows the flow of:

1. Working directory

  Here a developer can modify/create/delete files in their project, just do your thing....write your code etc.

2. Staging area

  Here are the files that the user has told Git are important and should be tracked. If a file is not here then Git will not care for the changes made to that file. Files are added to the staging area using the `git add` command. Use `man git add` for a more detailed overview. It's quite straight forward.

3. Repository

  Once files have been added to the staging area, using `git add`, they can then be committed to the repository. A commit represents a snapshot in the repo's file system. The difference between two commits as seen as a set of changes to a set of files, also synonymous to a patch (funnily enough a lot of modern patches come straight from Git commits). Also note that that your changes and repository are local and not automatically sent to your Git server, this must be done manually. As such one must commit changes to your repository and then push the commits to the remote server, but we will get to this a little later.

The benefit of having a staging area is that a user can create separate commits for different chunks of work. If you modified two separate files you could add each file to the staging area individually, commit the changes, thus creating a psudo patch for that file then add and commit the second file creating a separate patch for the second file. While this functionality will most likely not be that useful for you in ESPL, it is an important concept to grasp, especially for industry work where the generation of patches is very important. As you should not have random files contained within your patches, such as debug files, knowing how to control the contents of a commit is very important.

Storing changes to file in the staging area are done using the `git commit` command. See `man git commit` for details. We will see how this is done in practice shortly and it should become clear if it's not making complete sense at the moment.

## What is a Commit?

Now that we know the rough workflow of Git, I feel that it will help to make the entire process of Git and tracking changes clearer if what a commit is is outlined.

A commit holds the state of the repository at the moment when the commit was created. This state is just a node in a linked list of the repository's previous states, with the commit node's parent(s) being the commits that came before it during the development within the Git repository. Git does not store the delta of each file like other versioning control software but instead creates copies of changed files, unchanged files are thus able to be simply referenced, such that that unnecessary copies of unchanged file are not made. This allows the user to navigate through this linked list of commits to look at the repository's snapshots at different points in time. As such, Git is more or less a mini filesystem that has some powerful tooling to achieve some pretty nifty tricks.

## Lets Commit!

Now let's put this into practice. Git repositories almost always contain a README.md file. The README is responsible for giving an overview of and/or instructions for the project on the GitHub/GitLab page when one views the repository in the web interface, as you are probably doing now.

The README usually contains useful information outlining the project, how to build it, developer's contact information etc. As such, we will create and add one to our newly created ESPL repository. Please then create, in your ESPL repository, a `README.md` file. The `.md` signifys that it is a markdown fil, allowing for markdown formatting of the text. Markdown formatting information can be found [here](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links).

Please add your name and a quick description to the README then we will go through and add it.

``` bash
echo "# Your name here" > README.md
echo "A quick description" >> README.md
```

This will create the file and add your name and a description to the file, with your name being a H1 title.

Every time you make a change to the contents of your Git repository you can see the status of the repository using the command `git status`.

Running that now will show us a few things

```
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	README.md

nothing added to commit but untracked files present (use "git add" to track)
```

We can see that we are on our Master branch (we will cover branches a little later) and that we have the file `README.md` as an untracked file, meaning it is not in the staging area and would not be included in any commits.

Let's for testing purposes try and commit our README without adding it to the staging area. Looking at the manual for the `git commit` command (running `man git commit`). We can see the commands which can be used to add and remove files from the staging area (read the description section). Now a commit always requires a commit message, given using the `-m` option. Commit messages should always be precise and describe what changes have been implemented in this commit. Think of the commit message as a title/description for the patch that would be generated from the commit. As such to "attempt" to commit our README without adding it to the staging area we would run

``` bash
git commit -m "Added README"
```

We will now see that Git complains that nothing was added to the commit, meaning the staging area was empty. As we should all know by now, we need to add the `README.md` to the staging area. To do this we can either add the individual file or add all files in the repository. I would recommend avoiding adding all file where possible as you tend to include a lot of junk. We will cover how to avoid this a little later on.

For now add your README using

``` bash
git add README.md
```

Now attempting to commit should result in the output

```
[master (root-commit) 3c2b284] Added README
 1 file changed, 2 insertions(+)
 create mode 100644 README.md
```

Showing us a few things. It shows us our branch `master`, the beginning of the commit hash `3c2b284`, the commit message `Added README`, the changes made as well as the files added, in this case the `README.md`. To find out what the mode is read [here](https://stackoverflow.com/questions/737673/how-to-read-the-mode-field-of-git-ls-trees-output/8347325#8347325).

We have now successfully created a commit in our repository. Running `git log` we can see that the commit now appears in the repository's logs. In the log you can also see the entire commit hash which is used to identify that specific commit within your repo.

In a repo you will create many commits as you implement features and commit them, the commits will not be automatically visible to others who also have the repository on their machines or are looking through the web interface. Git does not automatically sync changes as it is designed to be usable offline, only syncing when told to. To then send your commits to the remote repository, stored on a Git server, you must `git push`. To understand what we are doing exactly when we are pushing we need to know a couple of things.

To push our code to the Git server we us the command `git push origin master`.

Breaking this command down we have:

 * `git push`, this is the command the tells Git to send all of the commits saved locally on your machine to the remote server.
 * `origin`, is the alias given to the remote server where our repository is stored. If you look into the `.git/config` file in your repositories root directory you will see something similar to the following

  ```
  ...                                                 
  [remote "origin"]                                                                
    url = git@git.alxhoff.com:alxhoff/espl-test.git                              
    fetch = +refs/heads/*:refs/remotes/origin/*                                   
  ...
  ```

  This is telling us that when we use `origin` we will be sending our commits to the server specified by that alias. It is possible to send to multiple servers at once, for instance a backup server, or to send to both a private and public server.

* `master`, tells Git which branch's commits we are wanting to send. We will cover branches soon.

Running `git push origin master` will show us the following

```
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Writing objects: 100% (3/3), 253 bytes | 253.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To git.alxhoff.com:alxhoff/espl-test.git
 * [new branch]      master -> master
```

which should be quick self-explanatory.

Now that we have covered how to add, commit and push we will stop using the ESPL repository and focus purely on this tutorial repository that you forked. The ESPL repository is there for you to use over the semester, read the exercise and project descriptions to see how your use of Git will be assessed. Using Git is required as part of the grading in this course, USE IT!

# Programming Challenge

Inside this repository there is a small programming challenge where you will learn about some more advanced features of Git, the basics of building a C project and also do some very basic programming exercises. The first step will be to start our C project. To do this you will need to get and merge the CMake project to your master branch, to do this we need to learn about branches and merging. First step it branching.

Git uses branches to allow for parallel development of code without interfering with the code on other peoples machines or without breaking your stable code base whilst you hack around some changes. How exactly branches are used is a personal preference or the preference of your company, but there are some good ideas to employ when using your Git branches.

We have already come across the master branch, as the name implies this is the root branch of the repository and it usually the most sacred of all branches. Good practice is to not develop directly on the master branch as the master branch should always have a stable version of your code that builds and runs, while it might not have all the latest features, it should be able to be demo'd at any moment in time (except maybe exactly during a merge). You should as such never push to master, only merge to master. Be prepared for impromptu requests to see your code running, it should thus be able to be run from your master branch always even if it lacks all the latest features.

As master is this stable branch that must never break, you might of guessed that all development should be done on other branches. This is correct. When working in large groups or on a project where you are swapping between implementing multiple features at the same time, each person or feature should be a branch. I would recommend towards having a branch for a feature as multiple people might work on a feature over the duration of a project. To understand the next concept we need to have a basic understanding of what merging is, while we will look at merging in practice shortly, a theoretical understanding is needed.

Merging, as the name implies, is the task of merging the code (the changes) from one branch into another. If you have a branch to implement a certain feature, you would then merge this feature into your master branch once the feature is completed. The merge process can become quite complex and involved but for now you should understand what merging aims to achieve. As you can imagine, merging large complex changes can become quite involved, while Git does a great job at handling most changes automatically it does not always manage on its own. As such, merging your changes into master can sometimes lead master to becoming unstable whilst the merge is handled. As such you can imagine that employing a merge branch to handle the merging of complicated code changes into one single delta can act as a good intermediary between your feature branches and the master branch.

Therefore it can be good practice to have a branch structure similar to the following

```
master ----- merging ----- feature A
                     |---- feature B
```

Thus any complicated merge conflicts will be contained to the merging branch and can be resolved there before being merge (via a less complex merge as the complex problems have now been resolved) into the master branch. We will cover merge errors and the likes later as your perform your own merges.

Let us now go to the merging branch. To check the branches that exist in the repository one can use the `git branch` command. A new repository might not show all of the branches as Git does not download all information when not required, to try and minimize the data required locally. `man git fetch` will detail how Git fetch can be used.

When no remote is specified the default `origin` is used. Run `git fetch` to thus retrieve all the branches and tags on the origin remote. Now run `git branch --all` to list all of the branches on the origin. We want a branch called `merging` where we will perform our merges before merging to master. To do this we need to first create a branch and then swap to this branch. To create a new branch simply use

``` bash
git branch merging
```
now if we list our branches using `git branch` you should now see that there is a `merging` branch. We now need to change to this branch so our modifications that we perform are done there. It should be noted that the new branch is a copy of this current branch, although if we were to continue modifying master then the merging branch would fall behind and would need to be brought back up to speed with master. But for now just checkout `merging` using the checkout command.

``` bash
git checkout merging
```
It is also good to note that this action of branching and checking out can be done in a single command by using the `-b` option with the `checkout` command.

``` bash
git checkout -b merging
```

# Merge Basics

Now that you have checked out your merging branch we are going to perform some merges. As this tutorial will also look into building C projects, using CMake specifically, we will using merging and other Git tools to pull a basic CMake project together.

Firstly we will want to make our Git server (origin remote) aware of this new branch we have created, as it does not get made aware of this change unless we tell it. Similarly to before we will use the `git push` command but this time our branch has changed.

As such please push the current branch using the previous command of

``` bash
git push ______ ______
```
You will need to fill in those two blanks.

Now back to the problem. You should be able to find a branch called `make`, check it out using your newly learnt checkout command. On this branch is the skeleton for our CMake project. Now to merge the `CMakeLists.txt` file, which is the core CMake file for any CMake build, into our merging branch. We need to use the `git merge` command. Details of this can be found in the manual, you should be able to run the correct `man` command yourself now to do this.

Merging is always done on the branch into which you wish to merge. If you wish to merge your `merging` branch into `master` you would first need to `git checkout master` and then merge `merging` into `master`. As we are wanting to merge the `make` branch into our current branch we don't need to change branches.

The `git merge` command handles the merging of files automatically, although it requires human intervention occasionally. We will get to this later. For now we simply want to merge the `CMakeLists.txt` into our current branch. As our branch does not have a `CMakeLists.txt` file the merge should not have any errors when performing this merge.

We can thus execute

``` bash
git merge make
```
This should give us an output along the lines of

``` bash
CMakeLists.txt | 12 ++++++++++++
1 file changed, 12 insertions(+)
create mode 100644 CMakeLists.txt
```
Telling us that a new file was created with 12 new insertions, 1 for each line in the file. Now if we run `git log` we will see the commits made on the make branch when this `CMakeLists.txt` file was added to the repo.

Now that we have got the commits from the make branch merged into our branch we should push these changes to the remote, running `git push` again will now show that the files have been pushed. If we rerun `git log` you will notice that the commit where the `CMakeLists.txt` file was commited has now changed from

``` bash
(HEAD -> merging, origin/make, make)
```
to
``` bash
(HEAD -> merging, origin/merging, origin/make, make)
```
meaning that this commit can now found be found in origin/merging and not just merging, origin/make and make. This annotation (`origin/`) signifies the remote branch (ie. the branch on the server). The branch merging is your local branch while the branch origin/merging is that on the remote.

# CMake

Now that we have merged our CMakeLists to our current branch we need to go about making the project build such that it is stable and is in a condition that we would be happy to have on `master`. Good practice when building code projects is to have a folder where all temporary and/or build files are kept such that your project folder doesn't become cluttered with temporary build files. Cleaning the build is also easier as all build files are clumped together.

A common standard practice is to use a `build` folder. As such create a build folder in your Git repo's root, such that the build folder and `CMakeLists.txt` are in the same folder.

Now running the command `man cmake` we can see that to execute a CMake script one simply has to call the command cmake and the path to the cmake script file. First navigate into the build directory and then execute `cmake ..` where `..` specifies the folder in which the CMake script can be found, while the current directory (build) is used as the build directory. Moving up a folder (`cd ..`) and running `git status` you can now see that the build directory is now untracked and has had changes done to it. Running `git status build` shows us that the build directory now includes a `CMakeCache.txt` and a directory `CMakeFiles`. These are the temporary files generated by CMake.

Now before we go ahead and actually get the CMake project building lets play it safe and add **all** of the current files in the Git to the staging area, commit and push them so that we have a safe point to return to. Do this yourself, using a meaningful commit message.

## .gitignore

When committing the files you will see a lot of new files being created in Git. These are all temporary build files and should not actually be added to Git. If you already was questioning what I was doing by adding all of these then pat yourself on the back, you were correct in thinking so. This is a common problem that people new to Git have in that they include all sorts of useless metadata files, build files and binaries to the Git repository so that they clutter the Git repository and make navigating around the branches difficult as you create little changes without meaning so that changing branches becomes more difficult. This will be something you will come across in the future. But for now we will now fix this error by using a file called the `.gitignore`.

The `.gitignore` is a hidden file that lives in the Git root and contains a list of files that should intentionally be left untracked. Meaning that changes to those files are not of concern to Git. A more detailed description of how to use this file can be found [here](https://git-scm.com/docs/gitignore).

For now we just want to tell Git that the build folder's contents should be left untracked. To do this we need to create the `.gitignore` file and put the build folder in it.

This can be done by runing
``` bash
echo "build/" > .gitignore
```
From the Git repo's root directory

## Removing Staging Cache

Now running Git status we can see that the `.gitignore` file is untracked but the files we wish to have untracked (the build folder) are still being tracked. This is because the files are in the staging cache and need to thus be removed before the gitignore will be applied to them. A common fix that is used is to simply remove all files from the staging cache and then add them back.

To do so run

``` bash
git rm -r --cached .
```
This will recursively remove tracked files from the staging cache. Running `git status` again will now show us that all of the files in the repo have been deleted, meaning deleted from the staging area. In the untracked files section you will now only see the README, CMakeLists and .gitignore as these files have not been ignored via the gitignore. Now we can add these files back and commit them using something such as "Actualizing gitignore" as the commit message. After pushing the new commit, if we look at the repo through the web interface, looking specifically at the files on the merging branch, you will see that the build files are not included. It is important to add all files that you do not want included in the repository to be added to the gitignore so that there is no way for them to become accidentally included in a commit, this makes you look like a Git noob if you are committing build files.


## Onwards With CMake

Now that we have solved that problem let us continue building our CMake project. Previously we saw that CMake complained that there were no sources given to the target foo. Let us pick through the CMake file so we understand what went wrong and what we need to fix it.

To do so jump to the branch `compiling`.

In your web browser, if you select the branch `compiling` you can read the README directly in the browser.

# Compiling C programs

The compiling of a C program takes place in three steps. Each carried out by CMake. In the following couple of exercises you will look at each step and how they work. This will hopefully mean I have less questions to answer later in semester.

The three steps are:
1. Preprocessing
  Handling of preprocessor directives to produce completed C files for compilation.
2. Compilation
  The creation of object files from C files.
3. Linking
  The compiled object files are linked together to form a binary file that represents the built program.

## Preprocessor

A big advantage that C has over interpreter based languages as well as other compiled languages, such as Java, is its precompiler. This preprocessor allows a programmer to use certain directives to simplify coding. The most basic analogy for what a lot of the preprocessor does can be thought of as "cut and paste", where chunks of code are pasted around to minimize the amount of manual code copying and/or search and replace the programmer must perform.

There are specific preprocessor directives, such as `#include` and `#define` which you should all be familiar with. One can also create conditional statements that allow for the preprocessor to either include or not include code sections. This is done with the directives `#if`, `#ifdef` and `#ifndef`. A common example of these directives would be when performing "feature inclusion" via compiled flags.

``` C
#ifdef USE_AMAZING_FEATURE
device_t dev = amazing_device
#else
device_t dev = NULL
#endif
```

### Include and Define Directives

#### Includes

The include directive should be one that everyone is familiar with (if you don't know it this tutorial is going to be extra fun for you). This directive is found at the top of most C files. Includes enable the inclusions (funny that) of header files that contain required function *declarations* (function prototypes) and any other data that is required to interact with the API that the header file exposes from the relevant `.c` file, eg. constant values. This is achieved by the preprocessor pasting the contents of the header file wherever the relevant `#include <filename>` directive is found. Remember this when trying to debug include errors.

#### Defines

The define directive is used for text substitution, allowing for few nifty little tricks when writing C code. Firstly the `#define` allows the programmer to set a flag or give a certain text literal a value, which is then substituted during the preprocessing step of the build process. Commonly called a "hash define". This gives a few advantages, outlines below are the key, and most common, advantages.

 * Setting flags.

  Using the `ifdef` conditional preprocessor statements one can set flags. For example a "debug" mode could be enabled using a Boolean debug flag that then allows for the inclusion of debug code, such as print statements

  ``` C
#define DEBUG_MA_CODEZ	1
...
#if DEBUG_MA_CODEZ
printf("Value waz %d", da_value);
#endif
...
```
 * Human readability.

 By using hash defines instead of magic numbers (should be avoided whenever possible) code is able to be a more easily read as it will real more like actual text. This is important when sharing code or developing with others. Your code should read like a book.

 ``` C
#define SMILEY_X_LOCATION   12
#define SMILEY_Y_LOCATION   34
void function_that_draws_smiley ( int x_position, int y_position ) {
  ...
}
...
void main( int argc, char **argv ) {
    ...
    function_that_draws_smiley( SMILEY_X_LOCATION, SMILEY_Y_LOCATION);
    return 0;
}
 ```
 * Centralizes frequently used variable values in one locations, making changing widely used value very easy.

  For example, if the smiley drawn in the previous example is drawn many times in your program and you need to shift its location a hash define allows for the smiley to be moved for all cases where its location's value is used. By changing one centralized value. Simply put, hash defined are slightly better magic numbers. A good example of this would be using the following

 ``` C
 #define PI   3.14
 ```
 should you decide that PI is better as 3.15 then you would be quickly and easily able to break your code by changing just one value :)

#### Macros

Now a more advanced use for defines is macros. Macros use the substitution of tokens with other tokens to allow for the generation of code. Macros are beneficial when the use of a function would be trivial and/or executionally slower.

  ``` C
#define CIRCLE_AREA(RADIUS)   (PI * RADIUS * RADIUS)
```
The use of the above macro produces more easily read code that is then evaluated into inline C code during precompilation. The precompiler would do the following, via substitution

  ```C
#define MY_CIRCLE_RADIUS  2
...
my_circle_area = CIRCLE_AREA(MY_CIRCLE_RADIUS)
```
Would become
``` C
my_circle_area = 3.14 * 2 * 2
```
To see some much more involved macros that are used in the auto generation of data structures in a state machine, look [here](https://github.com/alxhoff/Application_Interfacing_Governor/blob/master/AI_gov_phases.c).

## Compilation

Now the compilation of code is only one step in the process of building a program. After each C file is run through the preprocessor, so that all the preprocessor directives have been handled, the completed C files must then compiled into assembly code. This is done using a compiler, such as the GNU C Compiler (GCC). The assembly code must then be made into machine code that is actually usable by the target device. This is done by the assembler, which creates machine code from the assembly code. By modifying these pieces of software, collectively called a toolchain, you can change how the code is compiled. Various toolchains are available for different hardware architectures, such that the compiled code is compiled with regards to how the code executes on the target architecture. Compiling for a different architecture, such as compiling on an x86 laptop for a ARM based micro-controller, is known as cross compiling.

The file produced by the assembler is a binary file, the formats can vary (ELF, a.out, ...) but the idea is the same. The binary files are called objects, each object file contains the compiled code and exposes the symbols contained within the binary code. Symbols are the addresses of the variables and functions contained within a binary, they can be thought of as the "API" to the object file. The addresses of all the symbols within an object file are stored within a symbol table.

At this point all of your source files have been compiled into separate objects which are unaware of each other. Function calls to functions found in other object files are at this point pointing to an unknown memory locations, in an unknown binary file. These calls are stored as references to undefined addresses which are to be resolved in the last step of building a program, linking. If the completed program binary is to be able to execute, each function call needs to know where the pointed to code actually resides in memory. This is done by the third step in building a program, linking. Common errors pop up along the lines of "undefined reference" when a symbol cannot be resolved, meaning that the linking step was not able to be completed.

I should also mention that libraries, with which you are hopefully familiar with, are simply object files that can be reused by multiple programs such that the same code is not rewritten and/or recompiled unnecessarily.

## Linking

So we know now that our program is compiled into a number of object files (binary blobs) we need to resolve all of the references to the symbols that are pointed to and found in other object files. As the name implies, linking is the process of linking these references to the actual memory addresses in the appropriate object files. Linking to files within the same source code chunk is usually not that error prone. Most errors come from having to link against static libraries or source code found else where on a system or in another project. Common errors will be those that complain of either missing definitions (cannot find appropriate symbols to link against) or duplicate errors (multiple objects exposing the same symbol).

# CMake

So now that I have outlined a bit for you what happens when building a program, we will go through and build a demo program by using a program called CMake. CMake just helps in automating the build process a little, while not abstracting the process so much that one looses touch with what is happening. Using your newly discovered Git skills we will piece together a basic project and get it compiled and linked. You may have to apply some Git trickery along the way to get all the pieces ;).

So now that you have an idea of what goes into building a C project lets see how you can accomplish this using CMake. If we open the CMake file in this branch you should see the following

``` bash                                                         
project(git_tutorial)                                                            
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)                                  

set(CMAKE_BUILD_TYPE Debug)                                                      
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)                   

include_directories(include)                                                     

file(GLOB SOURCES "src/*.c")                                                     

add_executable(foo ${SOURCES})    
```

Now the first few lines should be quite self-explanatory. On the fourth line we set the output directory for our binary. Meaning we will need to create a `bin` directory in our repo's root. Do this now. The fifth line is where we tell CMake which directories we want to use as include directories. In the directories here is where make will then look for files that you include using `#include`. This CMake line equates then to the `-I` make build option. Another good common practice is to separate your `.c` source files from your `.h` source files. As can be seen in the CMake, we use a folder called `include` for the header files and a folder called `src` for the source files. Create the `include` folder so it sits alongside the bin and build directories. Following this we can see the `file` command. The file command is a file manipulation command used to achieve lots of different things. In this case it is used with `GLOB`. Glob is used to generate a list of files given one or more globbing expressions, storing the results in a variable, in this case `SOURCES`. From the provided globbing expression we can see that in this case the file command generates a list of all `.c` files that can be found in the `src` folder. Since we do not have this you will also need to create it.

The final line in the CMake lets CMake know that an executable should be built from the provided source files, in this case those stored in the `SOURCES` variable. This will also perform the required linking should there be more than one source file found, as there are going to be no object files external to our source files' directory.

Now we are almost there. We have the folder structure set up for our project but we are missing some code! We want to merge the new folder structures that we created back to our merging branch. The problem is that Git only tracks the contents of a folder and not folders themselves. As all of our folders are empty they would not be able to be tracked, commited and then merged to our `merging` branch. A convention of Git to keep Git directories that are empty are to add a `.gitkeep` file to them. This is a hack way of creating a reason for Git to track the folder. In this case we are in need of this folder structure for CMake and as such it is important that Git is able to track our folders. Let's touch a `.gitkeep` into each folder that is empty. `man touch` should help you understand what touching does.

Checking the status of your repo you should now see that you can track your empty `src`, `bin` and `include` directories as they all have `.gitkeep` files in them. Add and commit your folders with a meaningful commit message and then checkout your merging branch and merge the folders to your `merging` branch. Come back to this branch (`compiling`) when you have done that.

## Coding Challenge I

Now we are in need of the most the most fundamental of fundamentals to compile our project, a main function. As we will consider the main function a new feature you must perform the following steps:

 * Checkout a new branch to implement your features, branching from this branch.
 * Write a main function in an appropriate file in your project, that is to output "Hello ESPL" to the terminal.
 * Add, commit and PUSH the work you have done to the origin remote.
 * Merge the changes back to `merging`, pushing the result.
 * Come back to this branch to continue with the instructions below.

Now you should have at least one source file and be able to rerun your CMake command to generate the required make files for your project. If all went well in your build folder you should now see a Makefile that was generated from CMake. To then build your project you need to run the command `make` from within your build directory. If all went well you should now find a built binary in your bin directory with the same name as the executable specified in you `CMakeLists.txt`.

Navigate to your bin directory and execute the binary by using the `./` Linux convention. You should be greeted with "Hello ESPL".

Now we know roughly how to navigate around a Git repo, create, add and commit files as well as build a basic C project with an idea of what is happening behind the scenes. Before we look into the more advanced CMake features, such as linking libraries, you should merge your current project to master as it is now in a stable state. Binary files should not be included in your commits and should be left untracked. Modify your repository accordingly such the the binaries can never be accidentally added. Once that is done you will need to go to the `exercise` branch where you will need to use the Git logs, merging and the `git cherry-pick` command to get your exercise requirements and the library code. Useful articles can be found [here](https://www.git-tower.com/learn/git/faq/detached-head-when-checkout-commit) and [here](https://www.hacksparrow.com/how-to-merge-a-specific-commit-in-git.html) to explain the process.

One commit will contain the necessary `.h` and `.c` files for a static library that we will build called `espl_lib`. Another commit will contain a `.patch` for your CMake script to link the library. Checkout the commits, find the files, verify their contents and then use cherry pick to merge them to your merging branch. The instructions (in a separate `.md` file) to continue can also be found in a seperate commit.
