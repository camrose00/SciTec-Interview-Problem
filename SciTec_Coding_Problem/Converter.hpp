//
// Created by Cameron Rosenberger on 4/20/23.
//

#ifndef SCITEC_CODING_PROBLEM_FILE_READER_H
#define SCITEC_CODING_PROBLEM_FILE_READER_H

#include "LLA.hpp"
#include "ECEF.hpp"
#include <vector>

class Converter {
public:
    //Singleton
    static Converter * getInstance();

    /*LLA_to_ECEF
     * input: LLA
     * converts a single LLA point to ECEF
     * all units are in radians, seconds, and meters
     * math comes from LLAtoECEF.pdf
     * output: ECEF
     */
    static ECEF LLA_to_ECEF(LLA);
    /*read_convert
     * input: string filename, vector<ECEF>& dataset
     * opens the file given by filename, creates a LLA point, converts LLA to ECEF, adds to dataset
     * output: void
     */
    static void read_convert(std::string,std::vector<ECEF>&);

private:
    Converter();
};


#endif //SCITEC_CODING_PROBLEM_FILE_READER_H
