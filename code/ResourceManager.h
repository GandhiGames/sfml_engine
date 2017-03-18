//
//  ResourceManager.hpp
//  sfml_engine
//
//  Created by Robert Wells on 05/03/2016.
//  Copyright © 2016 Gandhi Games. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ResourcePath.hpp"

template<typename Derived, typename T>
class ResourceManager {
public:
    ResourceManager(const std::string &l_pathsFile)
    {
        LoadPaths(l_pathsFile);
    }
    
    virtual ~ResourceManager()
    {
        PurgeResources();
    }
    
    void PurgeResources(){
        printf("Purging all resources:\n");
        while(m_resources.begin() != m_resources.end()){
            printf("Removing: %s\n", m_resources.begin()->first.c_str());
            delete m_resources.begin()->second.first;
            m_resources.erase(m_resources.begin());
        }
        printf("Purging finished.\n");
    }
    
    T* GetResource(const std::string &l_id)
    {
        auto res = Find(l_id);
        return (res ? res->first : nullptr);
    }
    
    const std::string &GetPath(const std::string& l_id)
    {
        auto path = m_paths.find(l_id);
        return (path != m_paths.end() ? path->second : "");
    }
    
    bool RequireResource(const std::string& l_id)
    {
        auto res = Find(l_id);
        if(res){
            ++res->second;
            return true;
        }
        
        auto path = m_paths.find(l_id);
        
        if (path == m_paths.end()){
            std::cout << "path not found: " << l_id << std::endl;
            return false;
        }
        
        T* resource = Load(path->second);
        if (!resource){ return false; }
        
        m_resources.emplace(l_id, std::make_pair(resource, 1));
        
        return true;
    }
    
    bool ReleaseResource(const std::string& l_id)
    {
        auto res = Find(l_id);
        if (!res){ return false; }
        --res->second;
        if (!res->second){ Unload(l_id); }
        return true;
    }
    
protected:
    T* Load(const std::string& l_path)
    {
        return static_cast<Derived*>(this)->Load(l_path);
    }
    
private:
    std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
    std::unordered_map<std::string, std::string> m_paths;
    
    
    std::pair<T*,unsigned int>* Find(const std::string& l_id)
    {
        auto itr = m_resources.find(l_id);
        return (itr != m_resources.end() ? &itr->second : nullptr);
    }
    
    bool Unload(const std::string& l_id)
    {
        auto itr = m_resources.find(l_id);
        if (itr == m_resources.end()){ return false; }
        delete itr->second.first;
        m_resources.erase(itr);
        return true;
    }
    
    void LoadPaths(const std::string& l_pathFile)
    {
        std::ifstream paths;
        paths.open(resourcePath() + l_pathFile);
    
        if(paths.is_open()){
            std::string line;
            while(std::getline(paths,line)){

                std::stringstream keystream(line);
                std::string pathName;
                std::string path;
                keystream >> pathName;
                keystream >> path;
                
                if(pathName.empty() || path.empty()){
                    std::cerr << "Error in file: " << l_pathFile << std::endl;
                }else{
                    m_paths.emplace(pathName, path);
                }
                
            }
            paths.close();
            
            return;
        }
        
        printf("! Failed loading the path file: %s\n",l_pathFile.c_str());
    }
};



#endif /* ResourceManager_hpp */