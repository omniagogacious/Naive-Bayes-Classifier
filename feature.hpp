/*
 * feature.hpp
 *
 *  Created on: May 3, 2011
 *      Author: Ethan L. Schreiber
 *      Adapted from java code written by Andrew McGregor
 */

#ifndef FEATURE_HPP_
#define FEATURE_HPP_

#include <string>
#include <cstring>

using std::string;
/**
 * feature.hpp
 *
 * Stores counts and computes probabilities for one boolean feature.
 */

// DELETE THIS !!!!!
#include <iostream>
using std::cout;
using std::endl;

class Feature {

  /* counts[][] is a 2x2 matrix that stores for each of the
   * 2 classes (0 and 1), the number of training examples we've
   * seen that don't have the feature (0) or have it (1).
   *
   * So counts[0][0] would be the number of training examples that fall
   * into class 0, that don't have the feature.
   *
   * totalPerClass[] stores the number of training examples we've seen
   * per class.  So totalPerClass[i] should always equal
   * counts[i][0] + counts[i][1].
   */

protected:
  int m_counts[2][2];
  int m_totalPerClass[2];
  string m_toMatch;

public :
  Feature(string toMatch) : m_toMatch(toMatch) {

    // Initialize the counters to 0
    m_counts[0][0] = 0;
    m_counts[0][1] = 0;
    m_counts[1][0] = 0;
    m_counts[1][1] = 0;

    m_totalPerClass[0] = 0;
    m_totalPerClass[1] = 0;
  }

	int isFeaturePresent(string s) {
		size_t found = s.find(m_toMatch);
		bool featurePresent = (found != string::npos);
		if (featurePresent) {
			return 1;
		}
		else {
			return 0;
		}
    /* DONE
     *
     * Determine whether this feature occurs in the string.
     * Return 1 if the feature is present; 0 otherwise.
     */
  	}

  void addTrainingExample(int featurePresence, int classNumber) {
	/* counts[][] is a 2x2 matrix that stores for each of the
	   * 2 classes (0 and 1), the number of training examples we've
	   * seen that don't have the feature (0) or have it (1).
	*/
	
		m_counts[classNumber][featurePresence]++;
		m_totalPerClass[classNumber]++;
    /* YOUR CODE HERE
     *
     * Given the absence/presence of this feature for the given class,
     * update the counts used to compute the probabilities.
     *
     * classNumber = the number of the class for this example (0 or 1)
     * featurePresence = 0 or 1 stating the presence or absence of this feature
     */
  }

	double getProbOfFeatureGivenClass(int featurePresence, int classNumber) {
    /* YOUR CODE HERE
     *
     * What is the probability of this feature being absent/present for this class?
     * Use your counts, but make sure to smooth it by adding 1 to avoid probabilities of
     * absolute zero or one.
     */
		//.. you need to smooth it so there's never a 0 or 1 probability
		// (m_totalPerClass[classNumber]+2)
		double prob = m_counts[classNumber][featurePresence]+1;
		return prob;
  }
};

#endif
/* FEATURE_HPP_ */
