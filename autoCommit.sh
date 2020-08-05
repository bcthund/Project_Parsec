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
}

echo -e -n "${BLUE}Do you want to add/commit/push? ${GREEN}(y/n/a) ${NC}"
read mode
if [ "$mode" != "${mode#[YyAa]}" ] ;then
    if [ "$mode" != "${mode#[Aa]}" ]; then answer='Y'; fi

    # ==================================================================
    #   Add
    # ==================================================================
    if [ "$mode" != "${mode#[Yy]}" ]; then
        echo -e -n "${BLUE}Add ${GREEN}(y/n)? ${NC}"; read answer;
    fi
    
    if [ "$answer" != "${answer#[Yy]}" ] ;then
        cmd "git add ."
        cmd "git status"
        echo -e;
    fi
    
    # ==================================================================
    #   Commit
    # ==================================================================
    if [ "$mode" != "${mode#[Yy]}" ]; then
        echo -e -n "${BLUE}Commit ${GREEN}(y/n)? ${NC}"; read answer;
    fi
    
    if [ "$answer" != "${answer#[Yy]}" ] ;then
        cmd "git commit -F gitmessage.txt"
        echo -e;
    fi
    
    # ==================================================================
    #   Push
    # ==================================================================
    if [ "$mode" != "${mode#[Yy]}" ]; then
        echo -e -n "${BLUE}Push ${GREEN}(y/n)? ${NC}"; read answer;
    fi
    
    if [ "$answer" != "${answer#[Yy]}" ] ;then
        cmd "git push"
        echo -e;
    fi
    
    # ==================================================================
    #   Clear commit message file
    # ==================================================================
    if [ "$mode" != "${mode#[Yy]}" ]; then
        echo -e -n "${BLUE}Clear commit message file ${GREEN}(y/n)? ${NC}"; read answer;
    fi
    
    if [ "$answer" != "${answer#[Yy]}" ] ;then
        cmd "cat /dev/null > gitmessage.txt"
        echo -e;
    fi
    
    echo -e "${GREEN} DONE!\n\n"
fi
