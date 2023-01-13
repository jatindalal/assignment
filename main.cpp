// #include <iostream>
#include <bits/stdc++.h>

using namespace std;

class RBAC{
public:

void addAcessOnResourceToRole(string access_mode, string resource, string role) {
    access_on_resource_to_role[role][resource].insert(access_mode);
}

void addRoleToUser(string role, string user) {
    user_role[user] = role;
}

bool checkAccess(string user, string resource, string access_mode) {
    auto role = user_role[user];

    if (role == "") return false;

    auto access_modes_for_resource = access_on_resource_to_role[role][resource];

    if (access_modes_for_resource.empty()) return false;

    return access_modes_for_resource.count(access_mode);
}

private:
    // maps a user to given role
    unordered_map<string, string> user_role;

    // maps a given role to another map that maps a given resource to set of access modes
    unordered_map<string, map<string, set<string>>> access_on_resource_to_role;
};

int main() {
    string line;

    ifstream input_file("input.txt");

    RBAC rbac;

    while (getline(input_file, line)) {

        stringstream check1(line);
        string intermediate;
        vector<string> tokens;

        while(getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        if (tokens[0] == "addAccessOnResourceToRole") {
            auto access = tokens[1], resource = tokens[2], role = tokens[3];

            rbac.addAcessOnResourceToRole(access, resource, role);

        }
        else if (tokens[0] == "addRoleToUser") {
            auto role = tokens[1], user = tokens[2];

            rbac.addRoleToUser(role, user);
        }
        else if (tokens[0] == "checkAccess") {
            auto user = tokens[1], resource = tokens[2], access = tokens[3];

            bool hasAccess = rbac.checkAccess(user, resource, access);

            if (hasAccess)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }

    input_file.close();
    return 0;
}