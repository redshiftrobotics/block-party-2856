# Robotics 2013-2014

## Intro

This is the main repository for the SAAS Robotics team in the 2013-2014 FTC season.

## Setup - this is important!

SAAS Robotics also supports an application called EasyC. In order to support EasyC, please add the following to your `.git/config` file:

    [remote "origin"]
    	push = +refs/heads/master:refs/heads/gh-pages
    	push = +refs/heads/master:refs/heads/master

You may also set this by executing the following in a git shell:

    git config --add remote.origin.push +refs/heads/master:refs/heads/gh-pages
    git config --add remote.origin.push +refs/heads/master:refs/heads/master