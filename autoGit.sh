#!/bin/bash
grey='\e[0m\e[90m'
GREY='\e[1m\e[90m'
red='\e[0m\e[91m'
RED='\e[1m\e[31m'
green='\e[0m\e[92m'
GREEN='\e[1m\e[32m'
yellow='\e[0m\e[93m'
YELLOW='\e[1m\e[33m'
purple='\e[0m\e[95m'
PURPLE='\e[1m\e[35m'
white='\e[0m\e[37m'
WHITE='\e[1m\e[37m'
blue='\e[0m\e[94m'
BLUE='\e[1m\e[34m'
cyan='\e[0m\e[96m'
CYAN='\e[1m\e[36m'
NC='\e[0m\e[39m'

cmd(){
    echo -e ">> ${WHITE}$1${NC}";
    eval $1;
    echo -e;
}


echo -e -n "${BLUE}What do you want to do?${NC}\n"
echo -e -n "${YELLOW} 1,S) Status${NC}\n"
echo -e -n "${YELLOW} 2,C) Commit${NC}\n"
echo -e -n "${YELLOW} 3,B) Branch${NC}\n"
echo -e -n "${YELLOW} 4,T) Tag${NC}\n"
echo -e -n "${YELLOW} 5,X) Exit${NC}\n\n"
echo -e -n "${GREEN}(1-5)? ${NC}"
read mode
if [ "$mode" != "${mode#[1Ss]}" ] ;then
    cmd "git status"
    cmd "git branch -a"
elif [ "$mode" != "${mode#[2Cc]}" ] ;then
    echo -e -n "${BLUE}Do you want to add, commit and push? ${GREEN}(y/n/a) ${NC}"
    read answer1
    if [ "$answer1" != "${answer1#[YyAa]}" ] ;then
        if [ "$answer1" != "${answer1#[Aa]}" ]; then answer2='Y'; fi

        # ==================================================================
        #   Add
        # ==================================================================
        if [ "$answer1" != "${answer1#[Yy]}" ]; then
            echo -e -n "${BLUE}Add ${GREEN}(y/n)? ${NC}"; read answer2;
        fi
        
        if [ "$answer2" != "${answer2#[Yy]}" ] ;then
            cmd "git add ."
            cmd "git status"
        fi
        
        # ==================================================================
        #   Commit
        # ==================================================================
        if [ "$answer1" != "${answer1#[Yy]}" ]; then
            echo -e -n "${BLUE}Commit ${GREEN}(y/n)? ${NC}"; read answer2;
        fi
        
        if [ "$answer2" != "${answer2#[Yy]}" ] ;then
            if [ -s gitmessage.txt ]; then
                cmd "git commit -F gitmessage.txt"
            else
                echo -e -n "${BLUE}Commit Message${GREEN}? ${NC}"; read answer3;
                cmd "git commit -m \"${answer3}\""
            fi
        fi
        
        # ==================================================================
        #   Push
        # ==================================================================
        if [ "$answer1" != "${answer1#[Yy]}" ]; then
            echo -e -n "${BLUE}Push ${GREEN}(y/n)? ${NC}"; read answer2;
        fi
        
        if [ "$answer2" != "${answer2#[Yy]}" ] ;then
            cmd "git push -u origin $(git branch --show-current)"
        fi
        
        # ==================================================================
        #   Clear commit message file
        # ==================================================================
        if [ -s gitmessage.txt ]; then
            if [ "$answer1" != "${answer1#[Yy]}" ]; then
                echo -e -n "${BLUE}Clear commit message file ${GREEN}(y/n)? ${NC}"; read answer2;
            fi
            
            if [ "$answer2" != "${answer2#[Yy]}" ] ;then
                cmd "cat /dev/null > gitmessage.txt"
            fi
        fi
    fi
elif [ "$mode" != "${mode#[3Bb]}" ] ;then

    echo -e -n "${BLUE}Branch Options:\n"
    echo -e -n "${YELLOW}  1) New${NC}\n"
    echo -e -n "${YELLOW}  2) Switch${NC}\n"
    echo -e -n "${YELLOW}  3) Switch to Master${NC}\n"
    echo -e -n "${YELLOW}  4) List${NC}\n"
    echo -e -n "${YELLOW}  5) Merge${NC}\n"
    echo -e -n "${YELLOW}  6) Exit${NC}\n\n"
    echo -e -n "${GREEN}(1-6)? ${NC}"
    read answer1
    if [ "$answer1" != "${answer1#[1]}" ] ;then
        echo -e -n "${BLUE}New Branch Name${GREEN}? ${NC}"; read answer2;
        cmd "git checkout -b ${answer2}"
        cmd "git branch -a"
    elif [ "$answer1" != "${answer1#[2]}" ] ;then
        echo -e -n "${BLUE}Branch Name${GREEN}? ${NC}"; read answer2;
        cmd "git checkout ${answer2}"
        cmd "git branch -a"
    elif [ "$answer1" != "${answer1#[3]}" ] ;then
        cmd "git checkout master"
        cmd "git branch -a"
    elif [ "$answer1" != "${answer1#[4]}" ] ;then
        cmd "git branch -a"
    elif [ "$answer1" != "${answer1#[5]}" ] ;then
        MyBranch=$(git branch --show-current);
        cmd "git checkout master";
        cmd "git merge ${MyBranch} --no-ff";
        cmd "git push";
        cmd "git branch -d ${MyBranch}";
        cmd "git push origin --delete ${MyBranch}";
        cmd "git branch -a"
        #cmd "git remote prune origin";
        #cmd "git remote prune ${MyBranch}";
    fi
elif [ "$mode" != "${mode#[4Tt]}" ] ;then
    echo -e -n "${BLUE}Tag Options:\n"
    echo -e -n "${YELLOW}  1) New Lightweight${NC}\n"
    echo -e -n "${YELLOW}  2) New Annotated${NC}\n"
    echo -e -n "${YELLOW}  3) Delete${NC}\n"
    echo -e -n "${YELLOW}  4) List${NC}\n"
    echo -e -n "${YELLOW}  5) Exit${NC}\n\n"
    echo -e -n "${GREEN}(1-5)? ${NC}"
    read answer1
    if [ "$answer1" != "${answer1#[1]}" ] ;then
        echo -e -n "${BLUE}New Lightweight Tag Name${GREEN}? ${NC}"; read answer2;
        cmd "git tag -a ${answer2}"
        cmd "git show ${answer2}"
    elif [ "$answer1" != "${answer1#[2]}" ] ;then
        echo -e -n "${BLUE}New Annotated Tag Name${GREEN}? ${NC}"; read answer2;
        cmd "git tag ${answer2}"
        cmd "git show ${answer2}"
    elif [ "$answer1" != "${answer1#[3]}" ] ;then
        cmd "git tag"
        echo -e -n "${BLUE}Tag to delete${GREEN}? ${NC}"; read answer2;
        cmd "git tag -d ${answer2}"
        cmd "git push origin --delete ${answer2}"
        cmd "git tag"
    elif [ "$answer1" != "${answer1#[4]}" ] ;then
        cmd "git tag"
    fi
fi

echo -e -n "${GREEN}DONE!${NC}\n\n"
