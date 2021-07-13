#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define MAX_ID 100002

const int days_per_month[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int cumulative_days_per_month[13] = { 0,31,59,90,120,151,181,212,243,273,304,334 };

struct Record {
	int begin;
	int end;
	int class_id;
}records[MAX_ID];

struct Class {
	int begin;
	int end;
	int ratio;
	list<int> record;
}classes[MAX_ID];

list<int> total_record;

void init() {
	total_record.clear();
}
void destroy() {
	//?
}
int decoding_class(char mClasstime[]) {
	int hour = (mClasstime[0] - '0') * 10 + (mClasstime[1] - '0');
	int minute = (mClasstime[3] - '0') * 10 + (mClasstime[4] - '0');
	int second = (mClasstime[6] - '0') * 10 + (mClasstime[7] - '0');

	return hour * 3600 + minute * 60 + second;
}
int decoding_record(char mRecordtime[]) {
	int hour = (mRecordtime[11] - '0') * 10 + (mRecordtime[12] - '0');
	int minute = (mRecordtime[14] - '0') * 10 + (mRecordtime[15] - '0');
	int second = (mRecordtime[17] - '0') * 10 + (mRecordtime[18] - '0');

	return hour * 3600 + minute * 60 + second;
}
void decoding_date(char mRecordtimeBegin[], char mRecordtimeEnd[], Record& r) {
	int year = (mRecordtimeBegin[2] - '0') * 10 + (mRecordtimeBegin[3] - '0') - 19;
	int month = (mRecordtimeBegin[5] - '0') * 10 + (mRecordtimeBegin[6] - '0');
	int day = (mRecordtimeBegin[8] - '0') * 10 + (mRecordtimeBegin[9] - '0');

	r.begin = year * 365 * 86400 + cumulative_days_per_month[month - 1] * 86400 + day * 86400 + decoding_record(mRecordtimeBegin);

	year = (mRecordtimeEnd[2] - '0') * 10 + (mRecordtimeEnd[3] - '0') - 19;
	month = (mRecordtimeEnd[5] - '0') * 10 + (mRecordtimeEnd[6] - '0');
	day = (mRecordtimeEnd[8] - '0') * 10 + (mRecordtimeEnd[9] - '0');

	r.end = year * 365 * 86400 + cumulative_days_per_month[month - 1] * 86400 + day * 86400 + decoding_record(mRecordtimeEnd);
}
void newClass(int mClassId, char mClassBegin[], char mClassEnd[], int mRatio) {
	classes[mClassId].begin = decoding_class(mClassBegin);
	classes[mClassId].end = decoding_class(mClassEnd);
	classes[mClassId].ratio = ((classes[mClassId].end - classes[mClassId].begin + 1) * mRatio) / 100;
	classes[mClassId].record.clear();
}
void newRecord(int mRecordId, int mClassId, char mRecordBegin[], char mRecordEnd[]) {
	decoding_date(mRecordBegin, mRecordEnd, records[mRecordId]);
	records[mRecordId].class_id = mClassId;

	auto it = classes[mClassId].record.begin();
	for (; it != classes[mClassId].record.end(); it++) {
		if (records[*it].begin > records[mRecordId].begin) {
			classes[mClassId].record.insert(it, mRecordId);
			break;
		}
	}
	if (it == classes[mClassId].record.end()) {
		classes[mClassId].record.push_back(mRecordId);
	}

	total_record.push_back(mRecordId);
}
void changeRecord(int mRecordId, char mNewBegin[], char mNewEnd[]) {
	int mClassId = records[mRecordId].class_id;
	classes[mClassId].record.remove(mRecordId);

	decoding_date(mNewBegin, mNewEnd, records[mRecordId]);

	auto it = classes[mClassId].record.begin();
	for (; it != classes[mClassId].record.end(); it++) {
		if (records[*it].begin > records[mRecordId].begin) {
			classes[mClassId].record.insert(it, mRecordId);
			break;
		}
	}
	if (it == classes[mClassId].record.end()) {
		classes[mClassId].record.insert(it, mRecordId);
	}
}
int checkAttendance(int mClassId, char mDate[]) {
	int year = (mDate[2] - '0') * 10 + (mDate[3] - '0') - 19;
	int month = (mDate[5] - '0') * 10 + (mDate[6] - '0');
	int day = (mDate[8] - '0') * 10 + (mDate[9] - '0');

	int begin = year * 365 * 86400 + cumulative_days_per_month[month - 1] * 86400 + day * 86400;
	int end = begin + classes[mClassId].end;
	begin += classes[mClassId].begin;

	int chk_start, chk_end, running_time = 0;
	chk_start = begin;
	chk_end = end;

	for (auto it : classes[mClassId].record) {
		if (records[it].begin > end) break;
		if (records[it].begin >= chk_start) chk_start = records[it].begin;
		chk_end = (records[it].end >= end) ? end : records[it].end;

		if (chk_end >= chk_start) {
			running_time += chk_end - chk_start + 1;
			chk_start = chk_end + 1;
			if (running_time >= classes[mClassId].ratio) {
				return 1;
			}
		}
	}
	return 0;
}
int checkCheating() {
	for (auto first = total_record.begin(); first != total_record.end(); first++) {
		list<int>::iterator second = first;
		advance(second, 1);
		for (; second != total_record.end(); second++) {
			if (records[*first].class_id == records[*second].class_id) continue;
			if ((records[*first].begin < records[*second].end) && (records[*second].begin < records[*first].end)) {
				//cout << 1 << endl;
				return 1;
			}
		}
	}
	return 0;
}