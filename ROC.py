import numpy as np
import matplotlib.pyplot as plt
# vergeleiche nur die signale!!
# datenfiles fuer ROC Kurven
# ax fuer xlambda
# dx fuer deltaR
# cx fuer lambdamass
# ex fuer vertexpos
j, ax1, bx1, cx1, dx1, ex1 = np.genfromtxt("rocwerte_ssbar.txt", unpack=True)
j, ax2, bx2, cx2, dx2, ex2 = np.genfromtxt("rocwerte_ddbar.txt", unpack=True)
j, ax3, bx3, cx3, dx3, ex3 = np.genfromtxt("rocwerte_uubar.txt", unpack=True)

# auswertung der roc daten
totalssbar_XL = sum(ax1)
totalddbar_XL = sum(ax2)
totaluubar_XL = sum(ax3)
# tpr von s und fpr von d und fpr von u benoetigt
cuts = np.arange(100) # 0 bis 99
cuts_l1 = np.linspace(0, 49, 50)
cuts_l2 = np.linspace(50, 99, 50)
x = cuts_l1[::-1]
zusammen = np.concatenate((x, cuts_l2))
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

# vertex positions
# s - d
tpr7 = []
fpr7 = []
# s - u
tpr8 = []
fpr8 = []

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
    k = 0
    while k <= i:
        truePos3 += dx1[k]
        frueNeg3 += dx2[k]
        k += 1
    tpr3.append(truePos3 / totalssbar_XL)
    fpr3.append(1 - (frueNeg3 / totalddbar_XL))

for i in range(len(cuts)):
    truePos4 = 0
    frueNeg4 = 0
    k = 0
    while k <= i:
        truePos4 += dx1[k]
        frueNeg4 += dx3[k]
        k += 1
    tpr4.append(truePos4 / totalssbar_XL)
    fpr4.append(1 - (frueNeg4 / totaluubar_XL))

# for lambdaMass
# for i in range(len(cuts)):
#     truePos5 = 0
#     frueNeg5 = 0
#     k = 0
#     while k <= i:
#         truePos5 += cx2[k]
#         frueNeg5 += cx1[k]
#         k += 1
#     tpr5.append(truePos5 / totalddbar_XL)
#     fpr5.append(1 - (frueNeg5 / totalssbar_XL))
#
# for i in range(len(cuts)):
#     truePos6 = 0
#     frueNeg6 = 0
#     k = 0
#     while k <= i:
#         truePos6 += cx3[k]
#         frueNeg6 += cx1[k]
#         k += 1
#     tpr6.append(truePos6 / totaluubar_XL)
#     fpr6.append(1 - (frueNeg6 / totalssbar_XL))

for i in range(len(zusammen)):
    truePos5 = 0
    frueNeg5 = 0
    k = 0
    while k <= i:
        truePos5 += cx2[k]
        frueNeg5 += cx1[k]
        k += 1
    tpr5.append(truePos5 / totalddbar_XL)
    fpr5.append(1 - (frueNeg5 / totalssbar_XL))

for i in range(len(zusammen)):
    truePos6 = 0
    frueNeg6 = 0
    k = 0
    while k <= i:
        truePos6 += cx3[k]
        frueNeg6 += cx1[k]
        k += 1
    tpr6.append(truePos6 / totaluubar_XL)
    fpr6.append(1 - (frueNeg6 / totalssbar_XL))

# for vertex positions
for i in range(len(cuts)):
    truePos7 = 0
    frueNeg7 = 0
    k = 0
    while k <= i:
        truePos7 += ex2[k]
        frueNeg7 += ex1[k]
        k += 1
    tpr7.append(truePos7 / totalddbar_XL)
    fpr7.append(1 - (frueNeg7 / totalssbar_XL))

for i in range(len(cuts)):
    truePos8 = 0
    frueNeg8 = 0
    k = 0
    while k <= i:
        truePos8 += ex3[k]
        frueNeg8 += ex1[k]
        k += 1
    tpr8.append(truePos8 / totaluubar_XL)
    fpr8.append(1 - (frueNeg8 / totalssbar_XL))

# dieser plot nur zwischen ssbar und ddbar
plt.plot(fpr1, tpr1, "k--", label="X_Lambda")
plt.plot(fpr3, tpr3, "b--", label="DeltaR")
plt.plot(fpr5, tpr5, "g--", label="M_Lambda")
# plt.plot(fpr7, tpr7, "y--", label="origin pos.")
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
# plt.plot(fpr8, tpr8, "y--", label="origin pos.")
# plt.plot(fpr32, tpr32, "b--", label="DeltaR_alt1")
plt.plot([0,1], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity(u)")
plt.ylabel("sensitivity(s)")
plt.savefig("py_output/ROC_s_u.pdf")
plt.clf()
