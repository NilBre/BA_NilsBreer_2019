import numpy as np
import matplotlib.pyplot as plt
# vergeleiche nur die signale!!
# datenfiles fuer ROC Kurven
# fuer ax fuer xlambda bx fuer deltaR cx fuer lambdamass
j, ax1, bx1, cx1, dx1 = np.genfromtxt("rocwerte_ssbar.txt", unpack=True)
j, ax2, bx2, cx2, dx2 = np.genfromtxt("rocwerte_ddbar.txt", unpack=True)
j, ax3, bx3, cx3, dx3 = np.genfromtxt("rocwerte_uubar.txt", unpack=True)

# Notiz:
# die anderen beiden deltaR messungen sind richtiger(?),
# da muss nur die Reihenfolge der Histogramme getauscht werden,
# dann passt es.

# auswertung der roc daten
totalssbar_XL = sum(ax1)
totalddbar_XL = sum(ax2)
totaluubar_XL = sum(ax3)
# tpr von s und fpr von d und fpr von u benoetigt
cuts = np.arange(100)
# xlambda
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

# lambdamass
# s - d
tpr5 = []
fpr5 = []
# s - u
tpr6 = []
fpr6 = []

# # deltaR3
# # s - d
# tpr33 = []
# fpr33 = []
# # s - u
# tpr34 = []
# fpr34 = []
# for X_Lambda
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
    # truePos31 = 0
    # frueNeg31 = 0
    k = 0
    while k <= i:
        truePos3 += dx1[k]
        frueNeg3 += dx2[k]
        # truePos31 += dx2[k]
        # frueNeg31 += dx1[k]
        k += 1
    tpr3.append(truePos3 / totalssbar_XL)
    fpr3.append(1 - (frueNeg3 / totalddbar_XL))
    # tpr31.append(truePos31 / totalddbar_XL)
    # fpr31.append(1 - (frueNeg31 / totalssbar_XL))

for i in range(len(cuts)):
    truePos4 = 0
    frueNeg4 = 0
    # truePos32 = 0
    # frueNeg32 = 0
    k = 0
    while k <= i:
        truePos4 += dx1[k]
        frueNeg4 += dx3[k]
        # truePos32 += dx3[k]
        # frueNeg32 += dx1[k]
        k += 1
    tpr4.append(truePos4 / totalssbar_XL)
    fpr4.append(1 - (frueNeg4 / totaluubar_XL))
    # tpr32.append(truePos32 / totaluubar_XL)
    # fpr32.append(1 - (frueNeg32 / totalssbar_XL))

# for lambdaMass
for i in range(len(cuts)):
    truePos5 = 0
    frueNeg5 = 0
    k = 0
    while k <= i:
        truePos5 += cx2[k]
        frueNeg5 += cx1[k]
        k += 1
    tpr5.append(truePos5 / totalddbar_XL)
    fpr5.append(1 - (frueNeg5 / totalssbar_XL))

for i in range(len(cuts)):
    truePos6 = 0
    frueNeg6 = 0
    k = 0
    while k <= i:
        truePos6 += cx3[k]
        frueNeg6 += cx1[k]
        k += 1
    tpr6.append(truePos6 / totaluubar_XL)
    fpr6.append(1 - (frueNeg6 / totalssbar_XL))

# dieser plot nur zwischen ssbar und ddbar
plt.plot(fpr1, tpr1, "k--", label="X_Lambda")
plt.plot(fpr3, tpr3, "b--", label="DeltaR")
plt.plot(fpr5, tpr5, "g--", label="M_Lambda")
# plt.plot(fpr31, tpr31, "b--", label="DeltaR_alt1")
plt.plot([0,1], [1,0], "r-", label="random values")
# plt.plot(j, ax_neu1, "r.", label="ssbar")
# plt.plot(j, ax_neu2, "g.", label="ddbar")
# plt.plot(j, ax_neu3, "b.", label="uubar")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity(d)")
plt.ylabel("sensitivity(s)")
plt.savefig("py_output/ROC_s_d.pdf")
plt.clf()

plt.plot(fpr2, tpr2, "k--", label="X_Lambda")
plt.plot(fpr4, tpr4, "b--", label="DeltaR")
plt.plot(fpr6, tpr6, "g--", label="M_Lambda")
# plt.plot(fpr32, tpr32, "b--", label="DeltaR_alt1")
plt.plot([0,1], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity(u)")
plt.ylabel("sensitivity(s)")
plt.savefig("py_output/ROC_s_u.pdf")
plt.clf()
