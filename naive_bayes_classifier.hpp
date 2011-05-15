/*
 * naive_bayes_classifier.hpp
 *
 *  Created on: May 3, 2011
 *      Author: ethan
 */

#ifndef NAIVE_BAYES_CLASSIFIER_HPP_
#define NAIVE_BAYES_CLASSIFIER_HPP_


/**
 * Two-class naive Bayes classifier.
 */

#include "feature.hpp"
#include <vector>

#include <cctype>

using std::vector;

class NaiveBayesClassifier {

  /* "m_features" maintains a list of all the features we are considering
   * in this classifier.
   *
   * "m_classTotals" counts how many training examples we've seen for each
   * of the two classes (0 and 1).
   */
protected :
  vector<Feature> m_features;
  int m_classTotals[2];

	double getPriorProbability(int classNumber) {
		
    /* YOUR CODE HERE
     *
     * Compute and return the prior probability that a string belongs to a class.
     * This is P(C=classNum).
     */

		return (double)m_classTotals[classNumber] / (m_classTotals[0] + m_classTotals[1]);
  }

	double getLikelihood(int classNumber, string s) {
		double mapProb = 1;
		string lowerCaseVersion = "";
		for (size_t i = 0; i < s.size(); i++) {
			lowerCaseVersion += tolower(s[i]);
		}
		
		char feature = 'a';
		for (size_t i = 0; i < 26; i++) {
			// for each feature, aka, each letter of the alphabet
			// determine if feature is in s
			
			Feature ft = m_features[i];
			int featurePresence = ft.isFeaturePresent(lowerCaseVersion);
			mapProb *= ft.getProbOfFeatureGivenClass(featurePresence, classNumber);
		}
		
		return mapProb;
    /* YOUR CODE HERE
     *
     * Compute and return the likelihood of the class, given the features.
     * This is P(F1=f1 and F2=f2 and ... Fn=fn | C=classNumber)
     *   where f1, f2, ..., fn are 0 or 1 depending on the presence or absence
     *   of the feature in that string.
     */
  	}

public :
  NaiveBayesClassifier() {
	m_classTotals[0] = 0;  // initialize m_classTotals to 0;
	m_classTotals[1] = 0;
	char letter = 'a';
	for (int i = 0; i < 26; i++) {
		char ft = letter+i;
		string toMatch = "";
		toMatch += ft;
		Feature aFeature(toMatch);
		m_features.push_back(aFeature);
	}
	
    /* YOUR CODE HERE
     *
     * Create the set of features that we'll use.
     * For part 1 of the assignment, there are 26 features:
     * one for each letter of the alphabet.  So, you need to
     * create each feature and add it to m_features.
     */
  }

	void addTrainingExample(string s, int classNumber) {
		
		string lowerCaseVersion = "";
		for (size_t i = 0; i < s.size(); i++) {
			lowerCaseVersion += tolower(s[i]);
		}
		
		for (size_t i = 0; i < m_features.size(); i++) {
			if (m_features[i].isFeaturePresent(lowerCaseVersion) == 1) {
				m_features[i].addTrainingExample(1, classNumber);
			}
			else {
				m_features[i].addTrainingExample(0, classNumber);
			}
			m_classTotals[classNumber]++;
		}
    /* YOUR CODE HERE
     *
     * Given a string and its correct classification, update:
     * (1) the counts that are used to compute the likelihoods.
     *     Feature.addTrainingExample(featureVal, classNumber) should take care of this,
     *     but you need to determine whether the feature is present for each feature.
     * (2) the counts that are used to compute the prior probability
     */

  }

	int classify(string s) {
		double map0 = getLikelihood(0, s) * getPriorProbability(0);
		double map1 = getLikelihood(1, s) * getPriorProbability(1);
		return map0 > map1 ? 0 : 1;
		
    /* YOUR CODE HERE
     *
     * Compute and return the most probable class (0 or 1) that this string
     * belongs to, using the maximum a posteriori (MAP) decision rule.
     *
     * You can do this using calls to getPriorProbability and getLikelihood.
     * You do not need to call getPosteriorProbability.
     */
  }

	double getPosteriorProbability(int classNumber, string s) {
		
    /* YOUR CODE HERE
     *
     * Compute and return the probability that the given string belongs to
     * class classNumber.
     * This is P(C=classNumber | F1=f1 and F2=f2 and ... Fn=fn)
     *   where f1, f2, ..., fn are 0 or 1 depending on the presence or absence
     *   of the feature in that string.
     *
     * The code will be similar to classify, except that you need to also
     * need to use Bayes' rule and the law of total probability.
     *
     * Note that this function is not necessary for a working classifier!
     * That is, you don't need to call getPosteriorProbability inside of classify.
     */
		double numerator = getLikelihood(classNumber, s) * getPriorProbability(classNumber);
		double denominator = getLikelihood(0, s)*getPriorProbability(0) + getLikelihood(1, s)*getPriorProbability(1);
		return numerator / denominator;
  }

};

#endif /* NAIVE_BAYES_CLASSIFIER_HPP_ */
