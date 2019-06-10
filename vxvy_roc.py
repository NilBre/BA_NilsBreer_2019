import numpy as np
import matplotlib.pyplot as plt
# Notizen an mich:
# Die alternative version ueber TPR und FPR geht bei beiden gut
# warum die andere nicht

# datenfiles fuer ROC Kurven
j, left1, right1 = np.genfromtxt("ssbar_vxvy.txt", unpack=True)
j, left2, right2 = np.genfromtxt("ddbar_vxvy.txt", unpack=True)
j, left3, right3 = np.genfromtxt("uubar_vxvy.txt", unpack=True)

# auswertung der roc daten
# fuer deltaR:
totalssbar = left1[0] + right1[0]
totalddbar = left2[0] + right2[0]
totaluubar = left3[0] + right3[0]
# for ssbar - uubar comparison
tp_su = []
fp_su = []
tn_su = []
fn_su = []
tpr1 = []
fpr1 = []
sens1 = []
spec1 = []
# for ssbar - ddbar comparison
tp_sd = []
fp_sd = []
tn_sd = []
fn_sd = []
tpr2 = []
fpr2 = []
sens2 = []
spec2 = []

# fill the right arrays:
# calc all important variables
for i in range(len(left1)):
    tp_su.append(right1[i])
    fp_su.append(right3[i])
    tn_su.append(left3[i])
    fn_su.append(left1[i])

# fill FPR and TPR
for i in range(len(left1)):
    tpr1.append(right3[i] / totaluubar) # TPR
    fpr1.append(right1[i] / totalssbar) # FPR

# calc ROC with other way
for i in range(len(left1)):
    calc_sens1 = tp_su[i] / (tp_su[i] + fn_su[i])
    calc_spec1 = 1 - (tn_su[i] / (fp_su[i] + tn_su[i]))
    sens1.append(calc_sens1)
    spec1.append(calc_spec1)

for i in range(len(left1)):
    tp_sd.append(right1[i])
    fp_sd.append(right2[i])
    tn_sd.append(left2[i])
    fn_sd.append(left1[i])

# fill FPR and TPR
for i in range(len(left1)):
    tpr2.append(right2[i] / totalddbar) # TPR
    fpr2.append(right1[i] / totalssbar) # FPR

# calc ROC with other way
for i in range(len(left1)):
    calc_sens2 = tp_sd[i] / (tp_sd[i] + fn_sd[i])
    calc_spec2 = 1 - (tn_sd[i] / (fp_sd[i] + tn_sd[i]))
    sens2.append(calc_sens2)
    spec2.append(calc_spec2)

plt.plot(spec1, sens1, "b--", label="roc punkte DR (s-u)")
plt.plot(spec2, sens2, "k--", label="roc punkte DR (s-d)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity")
plt.ylabel("sensitivity")
plt.savefig("py_output/vxvy_normal.pdf")
plt.clf()

plt.plot(fpr1, tpr1, "b--", label="alt. DR (s-u)")
plt.plot(fpr2, tpr2, "k--", label="alt. DR (s-d)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.savefig("py_output/vxvy_tpr_fpr.pdf")
plt.clf()
