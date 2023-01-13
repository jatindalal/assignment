// #include <iostream>
#include <bits/stdc++.h>

using namespace std;

class RBAC{
public:

// void addAccess(string access_mode) {
//     access_modes.insert(access_mode);
// }

// void addResourec(string resource) {
//     resources.insert(resource);
// }

// void addRole(string role) {
//     roles.insert(role);
// }

// void addUser(string user) {
//     users.insert(user);
// }

// void addAccessOnResource(string access_mode, string resource) {
//     access_on_resource[resource].insert(access_mode);
// }

void addAcessOnResourceToRole(string access_mode, string resource, string role) {
    access_on_resource_to_role[role][resource].insert(access_mode);
}

void addRoleToUser(string role, string user) {
    user_role[user] = role;
}

bool checkAccess(string user, string resource, string access_mode) {
    auto role = user_role[user];

    cout << "role: " << access_mode;

    if (role == "") return false;

    auto access_modes_for_resource = access_on_resource_to_role[role][resource];

    cout << "set " << access_modes_for_resource.size();

    if (access_modes_for_resource.empty()) return false;

    for (auto& o: access_modes_for_resource) cout << o << "\n";

    return access_modes_for_resource.count(access_mode);
}

// private:
    // unordered_set<string> access_modes, roles, users, resources;
    // unordered_map<string, set<string>> access_on_resource;
    unordered_map<string, string> user_role;

    // unordered_map<string, set<string>> access_on_resource;
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
            cout << user << resource << access;

            cout << rbac.user_role[user];
            if (hasAccess)
                cout << "Yes\n";
            else
                cout << "No\n";
        }

        // cout << tokens[0] << ":" << tokens[1] << "sdf\n";
    }

    input_file.close();
    return 0;
}