/**
 *  Copyright 2010 by Benjamin J. Land (a.k.a. BenLand100)
 *
 *  This file is part of SJVM the Simple Java Virtual Machine.
 *
 *  SJVM is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SJVM is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SJVM. If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   ClassLoader.h
 * Author: Benjamin J. Land
 *
 * Created on November 26, 2008, 5:34 PM
 */

#ifndef _CLASSLOADER_H
#define	_CLASSLOADER_H

#include <map>
#include <string>
#include <vector>

class ClassPath {
public:
    virtual ~ClassPath() { }
    virtual int request(const char *name, unsigned char *&data) = 0;
    virtual void release(unsigned char *data) = 0;
};

class FolderClassPath : public ClassPath {
private:
    std::string path;
public:
    FolderClassPath(const char* path);
    
    virtual int request(const char *name, unsigned char *&data);
    virtual void release(unsigned char *data);
};

class BootstrapClassPath : public ClassPath {
private:
    std::vector<ClassPath*> paths;
    std::map<unsigned char*, ClassPath*> mapped;
public:
    virtual ~BootstrapClassPath();
    void add(ClassPath* path);
    virtual int request(const char *name, unsigned char *&data);
    virtual void release(unsigned char *data);
};

#include "Thread.h"

class ClassFile;
class SJVM;
class Mutex;

class ClassLoader {
private:
    std::map<std::string,ClassFile*> classes;
    ClassPath *bootstrap;
    Mutex mutex;
public:
    virtual ~ClassLoader();
    ClassLoader(ClassPath *classpath);
    ClassFile* load(const char *name, SJVM *jvm);
};

#endif	/* _CLASSLOADER_H */

