
# 净现值
def NPV(cashflow, r):
    return sum(c / (1 + r)**i for (i, c) in enumerate(cashflow))

# 内部回报率，对于bonds也叫到期回报率（Yield-To-Maturity）.
def IRR(cashflow):
    lo, hi = -1, 1
    delta = 1e-8
    # bisect for the r s.t. NPV = 0. 
    while True:
        r = (lo + hi) / 2
        npv = NPV(cashflow, r)
        if abs(npv) < delta:
            return r
        # break if it's inf
        if npv < 0:
            if abs(r - lo) < delta:
                return r
            hi = r
        else:
            if abs(r - hi) < delta:
                return r
            lo = r


cashflow = [-100, 30, 60, 40]
r = 0.1
print(NPV(cashflow, r))
print(IRR(cashflow))
