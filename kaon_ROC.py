import numpy as np
import matplotlib.pyplot as plt
# counts, xk, dr, mass
j, ax1, cx1, dx1 = np.genfromtxt("roc_kaon_ssbar.txt", unpack=True)
j, ax2, cx2, dx2 = np.genfromtxt("roc_kaon_ddbar.txt", unpack=True)
j, ax3, cx3, dx3 = np.genfromtxt("roc_kaon_uubar.txt", unpack=True)

# auswertung der roc daten
totalssbar_XL = sum(ax1)
totalddbar_XL = sum(ax2)
totaluubar_XL = sum(ax3)
# tpr von s und fpr von d und fpr von u benoetigt
cuts = np.arange(100) # 0 bis 99
x = cuts[::-1]
reverse = x
# x_k
# s - d
tpr1 = []
fpr1 = []
# s - u
tpr2 = []
fpr2 = []

# deltaR
# s - d
tpr3 = []
fpr3 = []
# s - u
tpr4 = []
fpr4 = []

# kaonmass
# s - d
tpr5 = []
fpr5 = []
# s - u
tpr6 = []
fpr6 = []

# for x_k
for i in range(len(cuts)):
    truePos = 0
    frueNeg = 0
    k = 0
    while k <= i:
        truePos += ax2[k]
        frueNeg += ax1[k]
        k += 1
    tpr1.append(truePos / totalddbar_XL)
    fpr1.append(1 - (frueNeg / totalssbar_XL))

for i in range(len(cuts)):
    truePos2 = 0
    frueNeg2 = 0
    k = 0
    while k <= i:
        truePos2 += ax3[k]
        frueNeg2 += ax1[k]
        k += 1
    tpr2.append(truePos2 / totaluubar_XL)
    fpr2.append(1 - (frueNeg2 / totalssbar_XL))

# for deltaR
for i in range(len(cuts)):
    truePos3 = 0
    frueNeg3 = 0
    k = 0
    while k <= i:
        truePos3 += cx1[k]
        frueNeg3 += cx2[k]
        k += 1
    tpr3.append(truePos3 / totalssbar_XL)
    fpr3.append(1 - (frueNeg3 / totalddbar_XL))

for i in range(len(cuts)):
    truePos4 = 0
    frueNeg4 = 0
    k = 0
    while k <= i:
        truePos4 += cx1[k]
        frueNeg4 += cx3[k]
        k += 1
    tpr4.append(truePos4 / totalssbar_XL)
    fpr4.append(1 - (frueNeg4 / totaluubar_XL))

# for kaonMass
for i in range(len(cuts)):
    truePos5 = 0
    frueNeg5 = 0
    k = 0
    while k <= i:
        truePos5 += dx2[k]
        frueNeg5 += dx1[k]
        k += 1
    tpr5.append(truePos5 / totalddbar_XL)
    fpr5.append(1 - (frueNeg5 / totalssbar_XL))

for i in range(len(cuts)):
    truePos6 = 0
    frueNeg6 = 0
    k = 0
    while k <= i:
        truePos6 += dx3[k]
        frueNeg6 += dx1[k]
        k += 1
    tpr6.append(truePos6 / totaluubar_XL)
    fpr6.append(1 - (frueNeg6 / totalssbar_XL))

# dieser plot nur zwischen ssbar und ddbar
plt.plot(fpr1, tpr1, "k--", label="X_k")
plt.plot(fpr3, tpr3, "b--", label="dR")
plt.plot(fpr5, tpr5, "g--", label="M_Kaon")
plt.plot([0,1], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity(d)")
plt.ylabel("sensitivity(s)")
plt.savefig("py_output/kaon_ROC_s_d.pdf")
plt.clf()

plt.plot(fpr2, tpr2, "k--", label="X_k")
plt.plot(fpr4, tpr4, "b--", label="dR")
plt.plot(fpr6, tpr6, "g--", label="M_Kaon")
plt.plot([0,1], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity(u)")
plt.ylabel("sensitivity(s)")
plt.savefig("py_output/kaon_ROC_s_u.pdf")
plt.clf()
