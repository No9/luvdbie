# luvdbie 

[![Build Status](https://travis-ci.org/No9/luvdbie.png?branch=master)](https://travis-ci.org/No9/luvdbie)

## Introduction 

Luvdbie (pronounced loved by) is a leveldb instance wrapped by libuv tcp-server.
It is designed to be a performant networked instance of leveldb that can be used as a standalone instance as well as providing al alternative levelDOWN implementation in networked database scenarios.

This work was inspired by [this article by @hij1nx](https://medium.com/p/37a93d4e0013) and the [work I did on memory usage in the current leveldb stack](https://github.com/rvagg/node-levelup/issues/171) 

## Install

```bash
$ npm install luvdbie -g
```

## Run

```
luvdbie 8085
```


