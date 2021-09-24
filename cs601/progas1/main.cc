/*
    Interval Matching Problem
    CS 601 Programming Assignment 1
    Sankalp Gambhir
    180260032
*/

#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include <tuple>

typedef std::vector<std::pair<int, int> > p;
typedef std::vector<int> v;

std::tuple<int, p, v > interval_scheduler(int, int, p&, v&, int);

int main(){
    int n, k;
    p avail;
    v jobtimes;

    // get inputs
    std::cin >> n >> k;

    for(int i = 0; i < n; i++){
        avail.emplace_back();
        std::cin >> avail.back().first >> avail.back().second;
    }
    for(int i = 0; i < k; i++){
        jobtimes.emplace_back();
        std::cin >> jobtimes.back();
    }

    // sort them for convenience
    std::sort(jobtimes.begin(), jobtimes.end());
    std::sort(avail.begin(), avail.end(), [](const std::pair<int, int> &a, std::pair<int, int> &b) -> bool{
                                                return (a.first < b.first);
                                            }
            );
    
    // now to solve the problem
    int assigned;
    std::tie(assigned, avail, jobtimes) = interval_scheduler(n, k, avail, jobtimes, 0);
    std::cout << assigned;

    return 0;
}

std::tuple<int, p, v> interval_scheduler(int n, int k, p& interval, v& job, int start){

    // base case
    if (n == 0){
        // no jobs to assign
        return std::make_tuple(0, interval, job);
    }

    int assigned = 0;

    // n-1 subproblem
    std::tie(assigned, interval, job) = interval_scheduler(n-1, k, interval, job, start+1);

    // have solution for 1..n
    // combine with 0 for 0..n
    for(auto j = (job.size()-1); j >= 0; j--){
        if(job[j] < interval[start].first){
            // did not find an assignable job
            break;
        }
        if(job[j] <= interval[start].second){
            // found a match
            // remove the job and interval
            job.erase(job.begin() + j);
            interval.erase(interval.begin()+start);
            assigned += 1;
            break;
        }
    }

    return std::make_tuple(assigned, interval, job);
}