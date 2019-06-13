import numpy as np
import matplotlib.pyplot as plt

# vergeleiche nur die signale!!

# datenfiles fuer ROC Kurven
# a: links vom cut, b: rechts vom cut
# DeltaR
j, aDR1, bDR1, af1, bf1 = np.genfromtxt("ssbar_werte.txt", unpack=True)
j, aDR2, bDR2, af2, bf2 = np.genfromtxt("ddbar_werte.txt", unpack=True)
j, aDR3, bDR3, af3, bf3 = np.genfromtxt("uubar_werte.txt", unpack=True)
# fuer ax fuer xlambda bx fuer deltaR
j, ax1, bx1 = np.genfromtxt("ssbar_werte_XL.txt", unpack=True)
j, ax2, bx2 = np.genfromtxt("ddbar_werte_XL.txt", unpack=True)
j, ax3, bx3 = np.genfromtxt("uubar_werte_XL.txt", unpack=True)

# auswertung der roc daten
# fuer deltaR:
# nur die ersten 100 zahlen, da ich nur 100 bins habe
ax_neu1 = ax1[0:100] # xlambda fuer ssbar
ax_neu2 = ax2[0:100] # xlambda fuer ddbar
ax_neu3 = ax3[0:100] # xlambda fuer uubar
bx_neu1 = bx1[0:100] # deltaR fuer ssbar
bx_neu2 = bx2[0:100] # deltaR fuer ddbar
bx_neu3 = bx3[0:100] # deltaR fuer uubar
totalssbar_XL = sum(ax_neu1)
totalddbar_XL = sum(ax_neu2)
totaluubar_XL = sum(ax_neu3)
# tpr von s und fpr von d und fpr von u benoetigt
cuts = np.arange(100)
# xlambda
# s - d
tpr1 = []
fpr1 = []
# s - u
tpr2 = []
fpr2 = []

# xlambda
# s - d
tpr3 = []
fpr3 = []
# s - u
tpr4 = []
fpr4 = []

# for X_Lambda
for i in range(len(cuts)):
    truePos = 0
    frueNeg = 0
    k = 0
    while k <= i:
        truePos += ax_neu2[k]
        frueNeg += ax_neu1[k]
        k += 1
    tpr1.append(truePos / totalddbar_XL)
    fpr1.append(1 - (frueNeg / totalssbar_XL))

for i in range(len(cuts)):
    truePos2 = 0
    frueNeg2 = 0
    k = 0
    while k <= i:
        truePos2 += ax_neu3[k]
        frueNeg2 += ax_neu1[k]
        k += 1
    tpr2.append(truePos2 / totaluubar_XL)
    fpr2.append(1 - (frueNeg2 / totalssbar_XL))

# for deltaR
for i in range(len(cuts)):
    truePos3 = 0
    frueNeg3 = 0
    k = 0
    while k <= i:
        truePos3 += bx_neu2[k]
        frueNeg3 += bx_neu1[k]
        k += 1
    tpr3.append(truePos3 / totalddbar_XL)
    fpr3.append(1 - (frueNeg3 / totalssbar_XL))

for i in range(len(cuts)):
    truePos4 = 0
    frueNeg4 = 0
    k = 0
    while k <= i:
        truePos4 += bx_neu3[k]
        frueNeg4 += bx_neu1[k]
        k += 1
    tpr4.append(truePos4 / totaluubar_XL)
    fpr4.append(1 - (frueNeg4 / totalssbar_XL))

# for i in range(len(aDR1)):
#     positiveRatio1.append(bf1[i] / totalf_s) # FPR
#     negativeRatio1.append(bDR1[i] / totalssbar_DR) # TPR
#
# # calc ROC with other way
# for i in range(len(aDR1)):
#     calc_sens1 = tp_s[i] / (tp_s[i] + fn_s[i])
#     calc_spec1 = 1 - (tn_s[i] / (fp_s[i] + tn_s[i]))
#     sens1.append(calc_sens1)
#     spec1.append(calc_spec1)
# # --------------------
# for i in range(len(aDR1)):
#     tp_d.append(bf2[i])
#     fp_d.append(bDR2[i])
#     tn_d.append(aDR2[i])
#     fn_d.append(af2[i])
#
# for i in range(len(aDR1)):
#     positiveRatio2.append(bf2[i] / totalf_d) # FPR
#     negativeRatio2.append(bDR2[i] / totalddbar_DR) # TPR
#
# # calc ROC with other way
# for i in range(len(aDR1)):
#     calc_sens2 = tp_d[i] / (tp_d[i] + fn_d[i])
#     calc_spec2 = 1 - (tn_d[i] / (fp_d[i] + tn_d[i]))
#     sens2.append(calc_sens2)
#     spec2.append(calc_spec2)
# # ----------------------
# for i in range(len(aDR1)):
#     tp_u.append(bf3[i])
#     fp_u.append(bDR3[i])
#     tn_u.append(aDR3[i])
#     fn_u.append(af3[i])
#
# for i in range(len(aDR1)):
#     positiveRatio3.append(bf3[i] / totalf_u) # FPR
#     negativeRatio3.append(bDR3[i] / totaluubar_DR) # TPR
#
# calc ROC with other way
# for i in range(len(aDR1)):
#     calc_sens3 = tp_u[i] / (tp_u[i] + fn_u[i])
#     calc_spec3 = 1 - (tn_u[i] / (fp_u[i] + tn_u[i]))
#     sens3.append(calc_sens3)
#     spec3.append(calc_spec3)

plt.plot(fpr1, tpr1, "b--", label="X_Lambda")
plt.plot(fpr3, tpr3, "k--", label="DeltaR")
plt.plot([0,1], [1,0], "r-", label="random values")
# plt.plot(j, ax_neu1, "r.", label="ssbar")
# plt.plot(j, ax_neu2, "g.", label="ddbar")
# plt.plot(j, ax_neu3, "b.", label="uubar")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity")
plt.ylabel("sensitivity")
plt.savefig("py_output/ROC_DeltaR.pdf")
plt.clf()

# plt.plot(negativeRatio1, positiveRatio1, "b--", label="alt. DeltaR, s")
# plt.plot(negativeRatio2, positiveRatio2, "k--", label="alt. DeltaR, d")
# plt.plot(negativeRatio3, positiveRatio3, "g--", label="alt. DeltaR, u")
# plt.plot([1,0], [1,0], "r-", label="random values")
# plt.grid()
# plt.legend()
# plt.savefig("py_output/ROC_DeltaR_alt.pdf")
# plt.clf()

# for ssbar
# tp_sd_x = []
# fp_sd_x = []
# tn_sd_x = []
# fn_sd_x = []
# pr1 = []
# nr1 = []
# SE1 = []
# SP1 = []
# # for ddbar
# tp_dd_x = []
# fp_dd_x = []
# tn_dd_x = []
# fn_dd_x = []
# pr2 = []
# nr2 = []
# SE2 = []
# SP2 = []
# # for uubar
# tp_uu_x = []
# fp_uu_x = []
# tn_uu_x = []
# fn_uu_x = []
# pr3 = []
# nr3 = []
# SE3 = []
# SP3 = []
#
# # calc important values
# for i in range(len(ax1)):
#     tp_sd_x.append(bx1[i])
#     fp_sd_x.append(b_fake1[i])
#     tn_sd_x.append(a_fake1[i])
#     fn_sd_x.append(ax1[i])
#
# # fill FPR and TPR
# for i in range(len(ax1)):
#     pr1.append(bx1[i] / totalssbar_XL)
#     nr1.append(b_fake1[i] / totalfakes_s)
#
# # calc ROC with other way
# for i in range(len(ax1)):
#     sensXL1 = tp_sd_x[i] / (tp_sd_x[i] + fn_sd_x[i])
#     specXL1 = 1 - (tn_sd_x[i] / (fp_sd_x[i] + tn_sd_x[i]))
#     SE1.append(sensXL1)
#     SP1.append(specXL1)
# # ----------------
# for i in range(len(ax2)):
#     tp_dd_x.append(bx2[i])
#     fp_dd_x.append(b_fake2[i])
#     tn_dd_x.append(a_fake2[i])
#     fn_dd_x.append(ax2[i])
#
# # fill FPR and TPR
# for i in range(len(ax2)):
#     pr2.append(bx2[i] / totalddbar_XL)
#     nr2.append(b_fake2[i] / totalfakes_d)
#
# # calc ROC with other way
# for i in range(len(ax2)):
#     sensXL2 = tp_dd_x[i] / (tp_dd_x[i] + fn_dd_x[i])
#     specXL2 = 1 - (tn_dd_x[i] / (fp_dd_x[i] + tn_dd_x[i]))
#     SE2.append(sensXL2)
#     SP2.append(specXL2)
# # ---------------------
# for i in range(len(ax3)):
#     tp_uu_x.append(bx3[i])
#     fp_uu_x.append(b_fake3[i])
#     tn_uu_x.append(a_fake3[i])
#     fn_uu_x.append(ax3[i])
#
# # fill FPR and TPR
# for i in range(len(ax3)):
#     pr3.append(bx3[i] / totaluubar_XL)
#     nr3.append(b_fake3[i] / totalfakes_u)
#
# # calc ROC with other way
# for i in range(len(ax3)):
#     sensXL3 = tp_uu_x[i] / (tp_uu_x[i] + fn_uu_x[i])
#     specXL3 = 1 - (tn_uu_x[i] / (fp_uu_x[i] + tn_uu_x[i]))
#     SE3.append(sensXL3)
#     SP3.append(specXL3)
#
# plt.plot(SP1, SE1, "b--", label="X_Lambda, s")
# plt.plot(SP2, SE2, "k--", label="X_Lambda, d")
# plt.plot(SP3, SE3, "g--", label="X_Lambda, u")
# plt.plot([1,0], [1,0], "r-", label="random values")
# plt.grid()
# plt.legend()
# plt.xlabel("1 - specificity")
# plt.ylabel("sensitivity")
# plt.savefig("py_output/ROC_XLambda.pdf")
# plt.clf()
#
# plt.plot(nr1, pr1, "b--", label="X_Lambda")
# plt.plot(nr2, pr2, "k--", label="X_Lambda")
# plt.plot(nr3, pr3, "g--", label="X_Lambda")
# plt.plot([1,0], [1,0], "r-", label="random values")
# plt.grid()
# plt.legend()
# plt.xlabel("FPR")
# plt.ylabel("TPR")
# plt.savefig("py_output/ROC_XLambda_alt.pdf")
# plt.clf()
