#include <iostream>
#include <memory>
class Associates{
public:
    void setDevelopment(const std::string& Development){
        m_Development = Development;
    }
    void setTesting(const std::string& Testing){
        m_Testing = Testing;
    }
    void setAppSupport(const std::string& AppSupport){
        m_AppSupport = AppSupport;
    }
    void open() const {
        std::cout<<"The Associates have "<<
        m_Development<<" Development, "<<
        m_Testing<<" Testing, "<<
        m_AppSupport<<" AppSupport."<<
        std::endl;
    }
private:
    std::string m_Development;
    std::string m_Testing;
    std::string m_AppSupport;
};

class ITCompany{
public:
    virtual ~ITCompany() = default;
    void createNewAssociates(){
        m_Associates = std::make_unique<Associates>();
    }
    Associates* getAssociates() {
        return m_Associates.release();
    }
    virtual void buildDevelopment() = 0;
    virtual void buildTesting() = 0;
    virtual void buildAppSupport() = 0;
protected:
    std::unique_ptr<Associates> m_Associates;
};

class ManagerITCompany:public ITCompany{
public:
    ~ManagerITCompany() override = default;
    void buildDevelopment() override {
        m_Associates->setDevelopment("Manager Development");
    }
    void buildTesting() override {
        m_Associates->setTesting("Manager Testing");
    }
    void buildAppSupport() override {
        m_Associates->setAppSupport("Manager AppSupport");
    }
};

class TeamLeadITCompany:public ITCompany{
public:
    ~TeamLeadITCompany() override = default;
    void buildDevelopment() override {
        m_Associates->setDevelopment("TeamLead Development");
    }
    void buildTesting() override {
        m_Associates->setTesting("TeamLead Testing");
    }
    void buildAppSupport() override {
        m_Associates->setAppSupport("TeamLead AppSupport");
    }
};

class Project{
public:
    void openAssociates() const {
        m_ITCompany->getAssociates()->open();
    }
    void createAssociates(ITCompany* ITCompany){
        m_ITCompany = ITCompany;
        m_ITCompany->createNewAssociates();
        m_ITCompany->buildDevelopment();
        m_ITCompany->buildTesting();
        m_ITCompany->buildAppSupport();
    }
private:
    ITCompany* m_ITCompany;
};

int main(){
    Project Project{};
    ManagerITCompany ManagerITCompany;
    Project.createAssociates(&ManagerITCompany);
    Project.openAssociates();

    TeamLeadITCompany TeamLeadITCompany;
    Project.createAssociates(&TeamLeadITCompany);
    Project.openAssociates();
}
