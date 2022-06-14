# Virus_Spread
This is a visualization program based on the SIR virus propagation model. The virus spread will be displayed on the terminal

## Background

Due to the continuous spread of novel coronavirus, the epidemic in all countries continues to spread, and the deterioration rate in many countries is faster than expected. Although relevant epidemic area isolation points have been established in all countries, the current epidemic has not been completely controlled, so how to effectively control the ecological environment risk brought by the epidemic is still an urgent problem to be solved. 

## SEIR Model

The classic SEIR model divides the population into S (Susceptible), I (Infected), E (Exposed), and R (Recovered). 

This model also assumes that all individuals in the population have the chance to be infected, and when the infected individuals recover, they will produce antibodies, that is, the recovered population R will not be infected again.  Considering the isolation measures for prevention and treatment of infectious diseases, Sq (isolation of susceptible persons), Eq (isolation of latent persons) and Iq (isolation of infected persons) were added to the population component of the model. 

In view of the fact that isolated infected persons will be immediately sent to designated hospitals for isolation and treatment, all these people are replaced by inpatients H in this model.  Furthermore, the original population S, I and E refer to the susceptible, infected and latent persons missed by isolation measures respectively. 

## Environmental risk diffusion model

This model is a new two-dimensional model established on the basis of SEIR model, and its purpose is to more intuitively show the process of ecological environmental risk caused by virus spreading in urban map through atmosphere, water and other media. 

