#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <string>
#include <limits>
class rats{
public:
    void run(){
        //setup here
        load("rats.json");

        //spawnRat("/home/caroline/fukinRats/","f","m","m");
        //spawnRat("/home/caroline/fukinRats/","m","f","f");

        realRats();//don't uncomment until function works x3
        realPartners();
        mainLoop();
    }
private:
    struct ratInfo{
        std::string path;
        std::string action = "searchingFood";
        std::string sex;
        std::string gender = "m";
        int maxHunger = 100;
        int hungerVal = 100;
        int maxHealth = 100;
        int health = 100;
        bool hasPartner = false;
        std::string partnerName;
        bool hasNestLoc = false;
        bool hasNest = false;
        std::string nestPath;
        int nestFood=0;
        bool alive = true;
        std::string sexuality = "f";//can't use normal terms otherwize I have to code more. use m,f,bi,all
        std::string parents[2];//WHY DIDN'T I USE AN INDEX 3:
        bool adult = true;
        int untilAdult = 10;
        bool deadParents = false;
        bool rat = false;//like someone who rats out to the police
        std::string name;
        bool parent = false;
        int childIndex;
        bool hasFood = false;
        int timesUp = 0;

    };
    std::vector<ratInfo> allTheRats;

    void load(const std::string& filename){
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening JSON file!\n";
        }

        nlohmann::json j;
        file >> j;
        file.close();

        allTheRats.clear();
        for (const auto& item : j) {
            ratInfo rat;

            rat.path = item["path"];
            rat.action = item["action"];
            rat.sex = item["sex"];
            rat.gender = item["gender"];
            rat.maxHunger = item["maxHunger"];
            rat.hungerVal = item["hungerVal"];
            rat.maxHealth = item["maxHealth"];
            rat.health = item["health"];
            rat.hasPartner = item["hasPartner"];
            rat.partnerName = item["partnerName"];
            rat.hasNestLoc = item["hasNestLoc"];
            rat.hasNest = item["hasNest"];
            rat.nestPath = item["nestPath"];
            rat.nestFood = item["nestFood"];
            rat.alive = item["alive"];
            rat.sexuality = item["sexuality"];
            rat.parents[0] = item["parents1"];
            rat.parents[1] = item["parents2"];
            rat.adult = item["adult"];
            rat.deadParents = item["deadParents"];
            rat.rat = item["rat"];
            rat.name = item["name"];
            rat.parent = item["parent"];
            rat.childIndex = item["childIndex"];

            rat.hasFood = item["hasFood"];

            rat.timesUp = item["timesUp"];
            rat.untilAdult = item["untilAdult"];

            allTheRats.push_back(rat);
        }
    }
    void save(const std::string& filename) {
        nlohmann::json j;

        for (int i = 0; i < allTheRats.size(); ++i) {
            auto& rat = allTheRats[i];
            j.push_back({
                {"path", rat.path},{"action", rat.action},{"sex",rat.sex},{"gender",rat.gender},{"maxHunger",rat.maxHunger},{"hungerVal",rat.hungerVal},{"maxHealth",rat.maxHealth},{"health",rat.health},{"hasPartner",rat.hasPartner},{"partnerName",rat.partnerName},{"hasNestLoc",rat.hasNestLoc},{"hasNest",rat.hasNest},{"nestPath",rat.nestPath},{"nestFood",rat.nestFood},{"alive",rat.alive},{"sexuality",rat.sexuality},{"parents1",rat.parents[0]},{"parents2",rat.parents[1]},{"adult",rat.adult},{"deadParents",rat.deadParents},{"rat",rat.rat},{"name",rat.name},{"parent",rat.parent},{"childIndex",rat.childIndex},{"hasFood",rat.hasFood},{"timesUp",rat.timesUp},{"untilAdult",rat.untilAdult}
            });
        }

        std::ofstream file(filename);
        file << j.dump(4); // Pretty-print with indent of 4 spaces
        file.close();
    }
    void mainLoop(){
        //will run forever in final program
        while(true){
            for(int i=0;i<allTheRats.size();i++){
                ratBehavior(allTheRats[i]);

            }
            save("rats.json");

        }
    }
    bool validPath(std::string path){
        return std::filesystem::exists(path);
    }
    bool validFile(std::string path, std::string fileName){
        return std::filesystem::exists(path+fileName);
    }
    void spawnRat(std::string path,std::string gender,std::string sex,std::string sexuality){
        //maybe randomaze rats stats (rstats)'
        //if(!validPath(path))return;
        ratInfo tmpRat;
        tmpRat.path = path;
        tmpRat.gender = gender;
        tmpRat.sex = sex;
        tmpRat.sexuality = sexuality;
        tmpRat.name=std::to_string(allTheRats.size());
        createRatFile(tmpRat);
        allTheRats.push_back(tmpRat);

    }
    void breedRat(ratInfo& rat1,ratInfo& rat2){
        if(ratTransQ(rat1)||ratTransQ(rat2)){
            std::cout<<"trans rats???\n";
        }
        if(gayRatQ(rat1,rat2)){
            std::cout<<"gay ass rats.\n";
        }
        if(intersexRatQ(rat1)||intersexRatQ(rat2)){
            std::cout<<"intersex rat???\n";
        }
        if(!moreRatQ(rat1,rat2)){
            return;
        }


        ratInfo tmpRat;
        tmpRat.name=std::to_string(allTheRats.size());
        tmpRat.adult=false;
        tmpRat.parents[0]=rat1.name;
        tmpRat.parents[1]=rat2.name;
        tmpRat.maxHealth=(rat1.maxHealth+rat2.maxHealth)/2;
        tmpRat.maxHunger=(rat1.maxHunger+rat2.maxHunger)/2;
        tmpRat.nestPath=rat1.nestPath;

        //randomize gender, sex, health, & hunger values

        //sex/gender
        srand(time(0));
        int randomNum = rand() % 101;
        if(randomNum==50||randomNum==49){
            tmpRat.sex="n";
            tmpRat.gender="n";
        }else if(randomNum<50){
            tmpRat.sex="m";
            tmpRat.gender="m";
        }else{
            tmpRat.sex="f";
            tmpRat.gender="f";
        }

        //sets gender if intersex or trans
        randomNum = rand() % 101;
        if(tmpRat.sex=="n"){
            if(randomNum<65){
                randomNum = rand() % 101;
                if(randomNum<50){
                    tmpRat.gender="m";
                }else{
                    tmpRat.gender="f";
                }
            }
        }else if(randomNum==1){
            //rat is trans
            randomNum = rand() % 101;
            if(randomNum==50||randomNum==49){
                tmpRat.gender="n";
            }else if(randomNum<50){
                tmpRat.gender="m";
            }else{
                tmpRat.gender="f";
            }
        }

        //randomizes/mixes stats
        randomNum = rand() % 101;
        if(randomNum<50){
            if(randomNum<25){
                tmpRat.maxHealth+=1;
                tmpRat.maxHunger-=1;
            }else{
                tmpRat.maxHealth-=1;
                tmpRat.maxHunger+=1;
            }
        }

        while(tmpRat.maxHealth+tmpRat.maxHunger!=200){
            if(tmpRat.maxHealth+tmpRat.maxHunger>200){
                randomNum = rand() % 101;
                if(randomNum<50){
                    tmpRat.maxHealth-=1;
                }else{
                    tmpRat.maxHunger-=1;
                }
            }else{
                randomNum = rand() % 101;
                if(randomNum<50){
                    tmpRat.maxHealth+=1;
                }else{
                    tmpRat.maxHunger+=1;
                }
            }
        }

        randomNum = rand() % 101;
        if(randomNum<25){
            tmpRat.sexuality="m";
        }else if(randomNum<50){
            tmpRat.sexuality="f";
        }else if(randomNum<75){
            tmpRat.sexuality="bi";
        }else{
            tmpRat.sexuality="pan";
        }
        randomNum = rand() % 101;
        if(randomNum<10){
            tmpRat.rat=true;
        }
        tmpRat.path=rat1.path;
        rat1.parent=true;
        rat2.parent=true;
        rat1.childIndex=allTheRats.size();
        rat2.childIndex=allTheRats.size();
        createRatFile(tmpRat);
        std::cout<<"rat made!"<<std::endl;
        allTheRats.push_back(tmpRat);

    }
    bool intersexRatQ(ratInfo& rat){
        if(rat.sex!="m"&&rat.sex!="f"){
            return true;
        }
        return false;
    }
    bool moreRatQ(ratInfo& rat1, ratInfo& rat2){
        //just ignore that I've added intersex rats, and not all of them would be infertle
        if((rat1.sex=="m"&&rat2.sex=="f")||(rat1.sex=="f"&&rat2.sex=="m")){
            return true;
        }
        return false;
    }
    bool gayRatQ(ratInfo& rat1, ratInfo& rat2){
        if(rat1.gender==rat2.gender){
            return true;
        }
        return false;
    }
    bool ratTransQ(ratInfo& rat){
        if(rat.sex!=rat.gender){
            return true;
        }
        return false;
    }
    void realRats(){
        for(int i=0;i<allTheRats.size();i++){
            if(!validFile(allTheRats[i].path,allTheRats[i].name+".jpg")){
                removeRat(i);
            }
        }
    }
    void removeRat(int index){
        allTheRats.erase(allTheRats.begin()+index);
    }
    void ratBehavior(ratInfo& rat){
        //TODO add rat behavior so rats can be rat like //done mostly
        //look for food when hunger is less than half
        //if sees food eat//
        //rest if health is low//
        //nest if healthy and full & doesn't have nest//
        //take nesting material to nest area
        //look for partner rat if rat is healthy with a nest
        //gay rats???
        //gay rats & rats without children adopt children ig x3
        //orphaned rats look for parents to adopt them and will probably starve if we're being honest

        //look for folders containing a large number of bytes for searching
        //try to nest near food ig
        //bring food to nest if not doing anything else
        if(rat.hasPartner&&!rat.hasNest){
            for(int i=0;i<allTheRats.size();i++){
                if(rat.partnerName==allTheRats[i].name){
                    if(allTheRats[i].hasNest){
                        rat.hasNest=true;
                        rat.hasNestLoc=true;
                        rat.nestPath=allTheRats[i].nestPath;
                    }
                }
            }
        }

        setBehavior(rat);
        //TODO add the actual behavior here //done probably
        if(!rat.alive)return;
        if(rat.adult){
            if(rat.action=="searchingFood"){
                if(rat.nestFood==false){
                    lookFood(rat);
                }else{
                    goNest(rat);
                }
            }else if(rat.action=="goingNest"){
                goNest(rat);
            }else if(rat.action=="restNoNest"){
                rat.hungerVal-=2*(rat.maxHealth-rat.health);
                rat.health=rat.maxHealth;
            }else if(rat.action=="FindNestLoc"){
                lookFood(rat);
            }else if(rat.action=="FindNestMaterials"){
                if(!rat.hasFood){
                    lookFood(rat);
                }else{
                    goNest(rat);
                }
            }else if(rat.action=="searchingMate"){
                lookFood(rat);
            }else if(rat.action=="goingNestSex"){//done
                if(rat.path==rat.nestPath){
                    int partnerIndex = 0;
                    for(int i=0;i<allTheRats.size();i++){
                        if(allTheRats[i].name==rat.partnerName){
                            partnerIndex=i;
                        }
                    }
                    if(rat.path==allTheRats[partnerIndex].path){
                        if(allTheRats[partnerIndex].action=="goingNestSex"){
                            if(!rat.parent){
                                breedRat(rat,allTheRats[partnerIndex]);
                            }
                        }
                    }
                }else{
                    goNest(rat);
                }
            }else if(rat.action=="foodToNest"){
                if(!rat.hasFood){
                    lookFood(rat);
                }else{
                    goNest(rat);
                }
            }
        }else{
            if(rat.action=="searchParent"){
                lookFood(rat);
            }else if(rat.action=="wait"){
                if(!rat.hasNest){
                    for(int i=0;i<allTheRats.size();i++){
                        if(allTheRats[i].name==rat.parents[0]&&allTheRats[i].hasNest){
                            rat.nestPath = allTheRats[i].nestPath;
                            rat.hasNest=true;
                        }
                    }
                }else{
                    goNest(rat);
                    if(rat.path==rat.nestPath){
                        if(rat.nestFood>0){
                            rat.nestFood--;
                            rat.hungerVal++;
                            rat.untilAdult--;
                            if(rat.untilAdult<=0){
                                noChild(rat);
                            }
                        }
                    }
                }
            }
        }
    }
    void setBehavior(ratInfo& rat){
        if(rat.adult){
            if(rat.hungerVal/rat.maxHunger<0.5){
                rat.action="searchingFood";
            }else if(rat.health/rat.maxHealth<0.5){
                if(rat.hasNest){
                    rat.action="goingNest";
                }else{
                    rat.action="restNoNest";
                }
            }else if(!rat.hasNest&&!rat.hasNestLoc){
                rat.action="FindNestLoc";
            }else if(rat.hasNestLoc&&!rat.hasNest){
                rat.action="FindNestMaterials";
            }else if(!rat.hasPartner){
                rat.action="searchingMate";
            }else if(!rat.parent){
                rat.action="goingNestSex";
            }else{
                rat.action="foodToNest";
            }
        }else{
            if(rat.deadParents){
                rat.action="searchParent";
            }else{
                rat.action="wait";
            }
        }
    }
    void biteFile(std::string Path){
        //TODO bite files
        //don't do this for a while
        std::filesystem::path filePath = Path;
        int fileSize = std::filesystem::file_size(filePath);

        fileSize/=2;

        if(fileSize<2000){
            std::string command;
            command = "rm -rf "+Path;
            std::system(command.c_str());
        }else{
            std::string command = "dd if="+Path+" of="+Path+"tmp bs=1 skip="+std::to_string(fileSize)+" conv=notrunc";
            std::system(command.c_str());
            command="mv "+Path+"tmp "+Path;
            std::system(command.c_str());
        }

    }
    void goNest(ratInfo& rat){
        //TODO add nest finding behavior //done probably!
        //go up directories until reach directory can lead to nest
        //if that's impossible somethings fucked



        int res = rat.nestPath.find(rat.path);
        if (res != std::string::npos){
            if(rat.path!=rat.nestPath){
                downPath(rat,rat.nestPath.substr(rat.path.size(),rat.nestPath.size()-1));
            }
        }else{
            upPath(rat);
        }

        if(rat.action=="goingNest"){
            rat.hungerVal-=rat.maxHealth-rat.health;
            rat.health=rat.maxHealth;
        }else if(rat.action=="FindNestMaterials"){
            if(rat.path==rat.nestPath){
                rat.hasNest=true;
                rat.hasFood=false;
            }
        }else if(rat.action=="foodToNest"){
            if(rat.path==rat.nestPath){
                rat.nestFood+=10;
                rat.hasFood=false;
            }
        }else if(rat.action=="wait"){
            //don't do anything x3
        }else if(rat.action=="searchingFood"){
            if(rat.path==rat.nestPath){
                rat.hungerVal++;
                rat.nestFood--;
            }
            normalizeNestFood(rat);

        }
    }
    void lookFood(ratInfo& rat){
        //TODO add food finding behavior //probaby done??????
        //check for large file in directory
        //look for directories with large file size
        //probably go up a few directories first?
        bool foundPath = false;
        bool largeEnough = false;
        bool foundFile = false;
        std::string filePath;
        std::string path;

        if(rat.timesUp<3){

            upPath(rat);
            rat.timesUp++;
        }else{
            for (const auto & entry : std::filesystem::directory_iterator(rat.path)){
                if(entry.is_regular_file()){
                    if(QeddibleFile(entry.path(),entry.file_size())){
                        foundFile=true;
                        filePath=entry.path();
                    }
                }
                if(entry.is_directory()){
                    recursiveChecks(entry.path(),largeEnough,foundPath,path);
                }
            }
        }
        if(foundFile){
            rat.timesUp=0;
        }else if(foundPath){
            downPath(rat,path.substr(path.find_last_of("/")+1,path.size()-1));
        }


        if(rat.action=="searchParent"){
            for(int i=0;i<allTheRats.size();i++){
                if(allTheRats[i].path==rat.path&&allTheRats[i].hasPartner){
                    rat.parents[0]=allTheRats[i].name;
                    rat.parents[1]=allTheRats[i].partnerName;
                    rat.deadParents=false;
                    if(allTheRats[i].hasNest){
                        rat.nestPath=allTheRats[i].nestPath;
                    }
                }
            }
        }else if(rat.action=="foodToNest"){
            if(foundFile){
                biteFile(filePath);
                rat.hasFood=true;
            }
        }else if(rat.action=="searchingMate"){
            for(int i=0;i<allTheRats.size();i++){
                if(allTheRats[i].path==rat.path){
                    if(canPair(rat,allTheRats[i])){
                        rat.hasPartner=true;
                        rat.partnerName=allTheRats[i].name;

                        allTheRats[i].hasPartner=true;
                        allTheRats[i].partnerName=rat.name;

                        //and they were roomates
                        if(allTheRats[i].hasNest){
                            rat.hasNest=true;
                            rat.hasNestLoc=true;
                            rat.nestPath=allTheRats[i].nestPath;
                        }else if(rat.hasNest){
                            allTheRats[i].hasNest=true;
                            allTheRats[i].hasNestLoc=true;
                            allTheRats[i].nestPath=rat.nestPath;
                        }
                    }
                }
            }
        }else if(rat.action=="FindNestMaterials"){
            if(foundFile){
                biteFile(filePath);
                rat.hasFood=true;
            }
        }else if(rat.action=="FindNestLoc"){
            if(foundFile){
                rat.hasNestLoc=true;
                rat.nestPath=filePath.substr(0,filePath.find_last_of("/")+1);
            }
        }else if(rat.action=="searchingFood"){
            if(foundFile){
                biteFile(filePath);
                rat.hungerVal+=10;
            }
        }
    }
    bool canPair(ratInfo& loneleyRat, ratInfo& potentialPartnerRat){
        if(potentialPartnerRat.hasPartner||loneleyRat.hasPartner){
            return false;
        }
        if(!potentialPartnerRat.adult){
            return false;
        }
        if(potentialPartnerRat.name==loneleyRat.name){
            return false;
        }
        //do same checks for both
        //fem attracted
        if(loneleyRat.sexuality=="f"&&potentialPartnerRat.gender!="f"){
            return false;
        }
        if(potentialPartnerRat.sexuality=="f"&&loneleyRat.gender!="f"){
            return false;
        }
        //masc attracted
        if(loneleyRat.sexuality=="m"&&potentialPartnerRat.gender!="m"){
            return false;
        }
        if(potentialPartnerRat.sexuality=="m"&&loneleyRat.gender!="m"){
            return false;
        }
        //2 attracted (technically only m or f which isn't neccisarally what bi means, but whatever)
        if(loneleyRat.sexuality=="bi"&&potentialPartnerRat.gender=="n"){
            return false;
        }
        if(potentialPartnerRat.sexuality=="bi"&&loneleyRat.gender=="n"){
            return false;
        }
        //pan attraction checks not required

        return true;
    }
    void createRatFile(ratInfo& rat){
        std::string location = "/home/caroline/fukinRats/pictures/";
        if(rat.gender!=rat.sex){
            location+="trans";
        }
        if(rat.rat){
            location+="rat";
        }
        location+="rat.jpg ";


        std::string command = "ln -s "+location+" "+rat.path+rat.name+".jpg";

        std::system(command.c_str());
    }
    void manageHunger(ratInfo& rat){
        if(rat.hungerVal>0){
            rat.hungerVal-=1;
        }else{
            rat.health-=1;
        }
    }
    void upPath(ratInfo& rat){

        std::string initialRat = rat.path+rat.name+".jpg ";
        //SHOULD NOT BE CODED LIKE THIS!!!
        std::string first = rat.path.substr(0,rat.path.find_last_of("/"));

        rat.path=first.substr(0,first.find_last_of("/")+1);



        if(rat.path!=""){
            std::string command = "mv "+initialRat+" "+rat.path+rat.name+".jpg ";
            std::system(command.c_str());
        }else{
            rat.path="/";
        }

        manageHunger(rat);
    }
    void downPath(ratInfo& rat,std::string path){
        std::string initialRat = rat.path+rat.name+".jpg ";

        rat.path+=path+"/";

        std::string command = "mv "+initialRat+" "+rat.path+rat.name+".jpg ";

        std::system(command.c_str());
        manageHunger(rat);
    }
    void normalizeNestFood(ratInfo& rat){
        if(!rat.adult){
            if(!rat.deadParents){
                for(int i=0;i<allTheRats.size();i++){
                    if(allTheRats[i].name==rat.parents[0]||allTheRats[i].name==rat.parents[1]){
                        allTheRats[i].nestFood=rat.nestFood;
                    }
                }
            }
        }else{
            if(rat.hasPartner){
                for(int i=0;i<allTheRats.size();i++){
                    if(allTheRats[i].name==rat.partnerName){
                        allTheRats[i].nestFood=rat.nestFood;
                    }
                }
            }
            if(rat.parent){
                allTheRats[rat.childIndex].nestFood=rat.nestFood;
            }
        }
    }
    void noChild(ratInfo& rat){
        rat.adult=true;
        rat.hasNestLoc=false;
        rat.hasNest=false;
        for(int i=0;i<allTheRats.size();i++){
            if(allTheRats[i].name==rat.parents[0]||allTheRats[i].name==rat.parents[1]){
                allTheRats[i].parent=false;
            }
        }
    }
    bool QeddibleFile(std::string filePath,int fileSize){
        //checks if file is a rat
        for(int i=0;i<allTheRats.size();i++){
            if(filePath.find(allTheRats[i].name+".jpg")!= std::string::npos){
                return false;
            }
        }
        if(filePath.find("fukinRats")!= std::string::npos){
            //TODO uncomment when rats are loose
            return false;
        }
        if(fileSize<2000){
            return false;
        }

        return true;
    }
    void recursiveChecks(const std::filesystem::path entryPath,bool& largeEnough,bool& foundPath,std::string& path){
        for(const auto & subEntry : std::filesystem::recursive_directory_iterator(entryPath)){
            if(subEntry.is_regular_file()){
                if(QeddibleFile(subEntry.path(),subEntry.file_size())){
                    if(subEntry.file_size()>200){
                        largeEnough=true;
                    }
                    //std::cout<<subEntry.path()<<std::endl;
                }
                if(largeEnough){
                    foundPath=true;
                    path=entryPath;
                    return;
                }
            }

        }

    }
    void realPartners(){
        bool valid = false;
        for(int i=0;i<allTheRats.size();i++){
            if(allTheRats[i].hasPartner){
                for(int iP=0;iP<allTheRats.size();iP++){
                    if(allTheRats[iP].name==allTheRats[i].partnerName){
                        valid=true;
                    }
                }
                if(!valid){
                    allTheRats[i].hasPartner=false;
                }
            }
        }
    }

};

int main(){
    rats app;
    app.run();
    return 0;
}


